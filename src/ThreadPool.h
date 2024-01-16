#pragma once

#include <functional>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>

// Represents a single task in the thread pool.
struct Task {
    std::function<void()> func;
};

// Manages a pool of threads to execute tasks concurrently.
class ThreadPool {
public:

    /**
     * Constructor: Initializes the thread pool with a given number of threads.
     *  @param numThreads The number of threads to be created in the pool.
     */
    explicit ThreadPool(size_t numThreads);

    /**
     * Destructor: Waits for all threads to finish and cleans up resources.
     */
    ~ThreadPool();

    /**
     * EnqueueJob: Adds a new job to the thread pool's task queue.
     *  @param job The function to be executed as a job in the thread pool.
     */
    void EnqueueJob(const std::function<void()>& job);

private:
    std::vector<std::thread> workers; // The threads that run the tasks.
    std::queue<Task> taskQueue;       // Queue of tasks to be executed.
    std::mutex queueMutex;            // Mutex for synchronizing access to the task queue.
    std::condition_variable condition; // Condition variable for thread synchronization.
    bool stop;                         // Flag to signal the threads to stop.

    /**
     * WorkerMain: The main loop executed by each thread in the pool.
     */
    void WorkerMain();
};
