#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t numThreads) : stop(false) {

    // Create worker threads and add them to the vector of workers.
    for (size_t i = 0; i < numThreads; ++i) {
        workers.emplace_back(std::thread(&ThreadPool::WorkerMain, this));
    }
}

ThreadPool::~ThreadPool() {
    {
        // Set the stop flag to signal threads to stop.
        std::unique_lock<std::mutex> lock(queueMutex);
        stop = true;
    }

    // Notify all worker threads to wake up and check the stop flag.
    condition.notify_all();
    // Wait for all worker threads to finish.
    for (auto &worker : workers) {
        worker.join();
    }
}

void ThreadPool::EnqueueJob(const std::function<void()>& job) {
    {
        // Lock the queue and add the new task to the task queue.
        std::unique_lock<std::mutex> lock(queueMutex);
        Task newTask;
        newTask.func = job;
        taskQueue.push(newTask);
    }

    // Notify one worker thread to pick up the new task.
    condition.notify_one();
}

void ThreadPool::WorkerMain() {
    while (true) {
        Task currentTask;
        {
            // Lock the queue and wait for a task or until signaled to stop.
            std::unique_lock<std::mutex> lock(queueMutex);
            while (!stop && taskQueue.empty()) {
                condition.wait(lock);
            }

            // Check if the thread should stop.
            if (stop && taskQueue.empty()) {
                return;
            }

            // Get the next task from the task queue.
            currentTask = taskQueue.front();
            taskQueue.pop();
        }

        // Execute the task.
        currentTask.func();
    }
}
