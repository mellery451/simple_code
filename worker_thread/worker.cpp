#pragma once

/*
 * Copyright (c) 2024 Remy van Elst <raymii.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <queue>
#include <string>
#include <iostream>

using namespace std::chrono_literals;

namespace raymii {

struct exampleWorkItem {
    std::string name;
    int waitSec = 5;
};

class classWithWorkerThread {
public:

    classWithWorkerThread()
    {
        // Start worker thread
        _threadRunning = true;
        _workerThread = std::thread(&classWithWorkerThread::functionThatProcessesWorkOnThread, this);
    }

    classWithWorkerThread(const classWithWorkerThread&) = delete;
    classWithWorkerThread& operator=(const classWithWorkerThread&) = delete;
    classWithWorkerThread(classWithWorkerThread&&) = delete;
    classWithWorkerThread& operator=(classWithWorkerThread&&) = delete;

    ~classWithWorkerThread()
    {
        // Stop worker thread
        {
            std::lock_guard<std::mutex> lock(_threadMutex);
            _threadRunning = false;
        }
        _threadCV.notify_one();
        if (_workerThread.joinable()) {
            _workerThread.join();
        }
    }

    void addSomethingToProcess(const exampleWorkItem &work)
    {
        { // scoped lock mutex before adding work item
            std::lock_guard<std::mutex> lock(_threadMutex);
            // add item to queue
            _itemsToProcess.emplace(work);
        } // lock is out of scope here

        // notify worker thread that new work is available
        _threadCV.notify_one();
    }

private:
    // methods related to Worker Thread
    void functionThatProcessesWorkOnThread()
    {
        // only process work while running. Otherwise, exit method.
        while (_threadRunning) {
            // Acquire mutex. Is unlocked during the cv wait call. When woken up, its locked again
            std::unique_lock<std::mutex> lock(_threadMutex);

            // wait until notified that new work is available.
            _threadCV.wait(lock, [&] {
                // When woken, check if it's not a spurious wakeup.
                // Either there is work to process: !_itemsToProcess.empty()
                // or the thread is stopping: !_threadRunning
                return !_itemsToProcess.empty() || !_threadRunning;
            });

            if (!_threadRunning) // extra check to see if we're stopped after wakeup
                break; // if so, gracefully do an early exit.

            // Start processing work item. Make sure queue is not empty
            if (!_itemsToProcess.empty())
            {
                // Retrieve item from queue
                exampleWorkItem workItem = std::move(_itemsToProcess.front());
                _itemsToProcess.pop();

                // Unlock mutex because processing can be time-consuming
                lock.unlock();

                // Process Item
                std::cout << "Start Processing item " << workItem.name << ", sleeping " << std::to_string(workItem.waitSec) << " seconds " ;
                for (int i = 0; i < workItem.waitSec; ++i)
                {
                    std::cout << ".";
                    std::this_thread::sleep_for(1s);
                }
                std::cout << "; Finished Processing item " << workItem.name << ";" << std::endl;

                // Lock mutex again after finishing time-consuming work
                lock.lock();
            }
            // End processing work item.
        }
    }

    std::queue<exampleWorkItem> _itemsToProcess;
    std::thread _workerThread;
    std::mutex _threadMutex;
    std::condition_variable _threadCV;
    std::atomic<bool> _threadRunning = false;
};

} //namespace raymii
