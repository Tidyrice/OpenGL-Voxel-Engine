#ifndef TS_QUEUE_H
#define TS_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

// REFERENCED FROM:
// https://www.geeksforgeeks.org/implement-thread-safe-queue-in-c/

template <typename T>
class ts_queue {
    public:
        ts_queue() = default;
        ~ts_queue() = default;

        void Push(const T& item) {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push(item);
            cond_.notify_one();
        }

        T Pop() { //waits (non-blocking) until queue is not empty, then pops and returns item
            std::unique_lock<std::mutex> lock(mutex_);

            cond_.wait(lock, [this] { return !queue_.empty(); }); //wait until queue is not empty

            T item = queue_.front();
            queue_.pop();
            return item;
        }

        bool Empty() {
            std::lock_guard<std::mutex> lock(mutex_);
            return queue_.empty();
        }

        void Clear() {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_ = std::queue<T>(); //clear queue
        }

    private:
        std::queue<T> queue_;
        std::mutex mutex_;
        std::condition_variable cond_;
};

#endif // TS_QUEUE_H
