#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>

template <typename T>
class ThreadSafeQueue {
public:
    ThreadSafeQueue()
    {
    }

    void enqueue(T obj)
    {
        std::lock_guard<std::mutex> lock(mutex);
        queue.push(std::move(obj));
        //        condition.notify_one();
    }
    bool isEmpty() const
    {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.empty();
    }
    T dequeue()
    {
        std::unique_lock<std::mutex> lock(mutex);
        //        while (queue.empty())
        //            condition.wait(lock);
        if (queue.empty())
            throw std::runtime_error("Trying to get object from empty queue");

        T val = std::move(queue.front());
        queue.pop();
        return val;
    }

private:
    std::queue<T> queue;
    mutable std::mutex mutex;
    std::condition_variable condition;
};
