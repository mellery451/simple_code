#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdint>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

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

    // Increment the semaphore
    void post() { count_.fetch_add(1, std::memory_order_release); }

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

    // Increment the semaphore
    void post() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
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

int main() {
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
