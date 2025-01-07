#ifndef TS_SET_QUEUE_H
#define TS_SET_QUEUE_H

#include <queue>
#include <unordered_set>
#include <mutex>

//queue that holds unique items

template <typename T, typename Hash = std::hash<T>>
class ts_set_queue {
    public:
        ts_set_queue() = default;
        ~ts_set_queue() = default;

        void Push(const T& item) {
            std::lock_guard<std::mutex> lock(mutex_);
            if (set_.count(item) > 0) {
                return;
            }
            queue_.push(item);
            set_.insert(item);
            cond_.notify_one();
        }

        T Pop() { //waits (non-blocking) until queue is not empty, then pops and returns item
            std::unique_lock<std::mutex> lock(mutex_);

            cond_.wait(lock, [this] { return !queue_.empty(); }); //wait until queue is not empty

            T item = queue_.front();
            queue_.pop();
            set_.erase(item);
            return item;
        }

        bool Empty() {
            std::lock_guard<std::mutex> lock(mutex_);
            return queue_.empty();
        }

        void Clear() {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_ = std::queue<T>(); //clear queue
            set_.clear();
        }

    private:
        std::queue<T> queue_;
        std::unordered_set<T, Hash> set_;
        std::mutex mutex_;
        std::condition_variable cond_;
};

#endif // TS_SET_QUEUE_H
