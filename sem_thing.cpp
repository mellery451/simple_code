#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdint>
#include <iostream>
#include <limits>
#include <mutex>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

// Semaphore with two implementations, plus a small test runner.
//
// Build (C++17, run from the directory containing this file):
//   mutex + condition_variable (default):
//     g++ -std=c++17 -Wall -Wextra -pthread sem_thing.cpp -o sem_thing
//   lock-free std::atomic (CAS loop, spins with yield):
//     g++ -std=c++17 -Wall -Wextra -pthread -DSEM_USE_ATOMIC sem_thing.cpp -o sem_thing
//
// Build with CMake (target "sem_thing"; the binary is build/sem_thing):
//     cmake -S . -B build [-DSEM_USE_ATOMIC=ON]
//     cmake --build build --target sem_thing
//   Note: this configures the whole project, which needs libcheck installed and
//   a CMake that accepts the top-level CMakeLists.txt (it has no
//   cmake_minimum_required). If configure reports errors, the Makefile is still
//   generated and the sem_thing target builds, but the g++ commands above are
//   the reliable route. Re-configure with -DSEM_USE_ATOMIC=ON/OFF to switch
//   implementations.
//
// Run the test runner (reads from stdin):
//     ./sem_thing < input.txt          or      printf '1 3\n0 100\n10 50\n20 10\n' | ./sem_thing
//   Input format: <initial value> <num threads>, then one "<waitTime> <postTime>"
//   line (ms) per thread.
//
//   Input                                  Result
//   -------------------------------------  ------------------------------------
//   1 3 / 0 100 / 10 50 / 20 10            SUCCESS, exit 0
//   0 2 / 0 50 / 100 10                    error: initial semaphore value must be >= 1 (got 0), exit 1
//   -1 2 / 0 50 / 100 10                   error: initial semaphore value must be >= 1 (got -1), exit 1
//   2 3 / 0 50 / 10 -5 / 20 10             error: thread times must be >= 0, exit 1
//   (error text goes to stderr; "/" above separates input lines)
//
// Run the self-test (no stdin) to check Semaphore directly, including the
// post() overflow check at UINT32_MAX:
//     ./sem_thing --selftest
//   Prints PASS/FAIL per check, exit 0 if all pass, 1 otherwise.
//
// All of the above give the same results for both Semaphore implementations.

// Select the implementation at compile time:
//   default:            mutex + condition_variable
//   -DSEM_USE_ATOMIC:   lock-free std::atomic (CAS loop, spins with yield)
#ifdef SEM_USE_ATOMIC

class Semaphore {
public:
    explicit Semaphore(uint32_t initialVal) : count_(initialVal) {}

    Semaphore(const Semaphore &) = delete;
    Semaphore &operator=(const Semaphore &) = delete;

    // Wait for the semaphore to be greater than 0, and then decrement the semaphore
    void wait() {
        uint32_t cur = count_.load(std::memory_order_relaxed);
        for (;;) {
            if (cur == 0) {
                // C++17 has no atomic wait, so yield and re-check
                std::this_thread::yield();
                cur = count_.load(std::memory_order_relaxed);
            } else if (count_.compare_exchange_weak(cur, cur - 1,
                                                    std::memory_order_acquire,
                                                    std::memory_order_relaxed)) {
                return;
            }
            // on CAS failure, cur was refreshed with the current value; retry
        }
    }

    // Increment the semaphore; throws std::overflow_error if already at max
    //
    // A CAS loop is needed so the max check and the increment are one atomic
    // step. If overflow doesn't matter (a count above UINT32_MAX is then
    // undefined, and wraps to 0), this simpler version can replace it:
    //
    //     void post() { count_.fetch_add(1, std::memory_order_release); }
    //
    // Don't "fix" that by checking max before the fetch_add, or by undoing it
    // after: another thread can change the count in between, so the check races.
    void post() {
        uint32_t cur = count_.load(std::memory_order_relaxed);
        do {
            if (cur == std::numeric_limits<uint32_t>::max()) {
                throw std::overflow_error("Semaphore::post: count overflow");
            }
        } while (!count_.compare_exchange_weak(cur, cur + 1,
                                               std::memory_order_release,
                                               std::memory_order_relaxed));
    }

private:
    std::atomic<uint32_t> count_;
};

#else

class Semaphore {
public:
    explicit Semaphore(uint32_t initialVal) : count_(initialVal) {}

    Semaphore(const Semaphore &) = delete;
    Semaphore &operator=(const Semaphore &) = delete;

    // Wait for the semaphore to be greater than 0, and then decrement the semaphore
    void wait() {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this] { return count_ > 0; });
        --count_;
    }

    // Increment the semaphore; throws std::overflow_error if already at max
    void post() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (count_ == std::numeric_limits<uint32_t>::max()) {
                throw std::overflow_error("Semaphore::post: count overflow");
            }
            ++count_;
        }
        cv_.notify_one();
    }

private:
    std::mutex mutex_;
    std::condition_variable cv_;
    uint32_t count_;
};

#endif

// Test runner:

struct ThreadArgs {
    int waitTime;  // ms to sleep before waiting
    int postTime;  // ms to sleep before posting
};

void testThread(Semaphore &sema, ThreadArgs args) {
    std::this_thread::sleep_for(std::chrono::milliseconds(args.waitTime));
    sema.wait();

    std::this_thread::sleep_for(std::chrono::milliseconds(args.postTime));
    sema.post();
}

// Self-test (run with --selftest): exercises Semaphore directly, covering
// cases the stdin runner can't reach, such as a count at UINT32_MAX.
static bool selfTest() {
    bool ok = true;
    auto check = [&ok](bool cond, const char *what) {
        std::cout << (cond ? "PASS: " : "FAIL: ") << what << "\n";
        ok = ok && cond;
    };

    // post() succeeds up to UINT32_MAX, throws past it, and leaves the count alone
    Semaphore s(std::numeric_limits<uint32_t>::max() - 1);
    bool threw = false;
    try { s.post(); } catch (const std::overflow_error &) { threw = true; }
    check(!threw, "post() from max-1 to max does not throw");

    threw = false;
    try { s.post(); } catch (const std::overflow_error &) { threw = true; }
    check(threw, "post() at max throws std::overflow_error");

    // the failed post must not have changed the count: wait() frees exactly one
    // slot, so one post succeeds and the next throws again
    s.wait();
    threw = false;
    try { s.post(); } catch (const std::overflow_error &) { threw = true; }
    check(!threw, "post() after wait() at max succeeds");

    threw = false;
    try { s.post(); } catch (const std::overflow_error &) { threw = true; }
    check(threw, "post() back at max throws again");

    return ok;
}

int main(int argc, char *argv[]) {
    if (argc > 1 && std::string(argv[1]) == "--selftest") {
        return selfTest() ? 0 : 1;
    }

    // Parse in data
    // First value is the semaphore initial value
    // Must be >= 1: every thread waits before it posts, so with 0 all threads
    // block in wait() forever. Read signed so a negative value isn't wrapped.
    int initialVal = 0;
    if (!(std::cin >> initialVal)) return 0;
    if (initialVal < 1) {
        std::cerr << "error: initial semaphore value must be >= 1 (got " << initialVal << ")\n";
        return 1;
    }

    Semaphore testSemaphore(static_cast<uint32_t>(initialVal));

    // Second value is the number of threads
    size_t numThreads = 0;
    if (!(std::cin >> numThreads)) return 0;

    std::vector<std::thread> threads;
    threads.reserve(numThreads);

    // Each thread has two values: the amount of time to sleep before waiting,
    // and the amount of time to sleep before posting. Both are in ms
    for (size_t i = 0; i < numThreads; i++) {
        ThreadArgs args{};
        if (!(std::cin >> args.waitTime >> args.postTime)) break;
        if (args.waitTime < 0 || args.postTime < 0) {
            std::cerr << "error: thread times must be >= 0\n";
            for (auto &t : threads) t.join();
            return 1;
        }

        threads.emplace_back(testThread, std::ref(testSemaphore), args);
    }

    for (auto &t : threads) {
        t.join();
    }

    // If we got here, success!
    std::cout << "SUCCESS\n";
    return 0;
}
