#ifndef QUEUE_H
#define QUEUE_H
#include <queue> // 包含队列容器的头文件
#include <condition_variable> // 包含条件变量的头文件
#include <mutex> // 包含互斥锁的头文件

template <typename T>
class Queue
{
public:
    Queue(); // 构造函数
    ~Queue(); // 析构函数

    // 中断队列操作
    void Abort()
    {
        abort_ = 1; // 设置中断标志为1
        cond_.notify_all(); // 唤醒所有等待的线程
    }

    // 将元素压入队列
    int Push(T val)
    {
        std::lock_guard<std::mutex> lock(mutex_); // 使用互斥锁保护共享资源
        if (abort_ == 1) // 如果中断标志为1
        {
            return -1; // 返回错误码
        }
        queue_.push(val); // 将元素压入队列
        cond_.notify_one(); // 唤醒一个等待的线程
        return 0; // 返回成功码
    }

    // 从队列中弹出元素
    int Pop(T &val, const int timeout = 0)
    {
        std::unique_lock<std::mutex> lock(mutex_); // 使用独占性互斥锁保护共享资源
        if (queue_.empty()) // 如果队列为空
        {
            // 等待push操作或者超时唤醒
            cond_.wait_for(lock, std::chrono::milliseconds(timeout), [this]
                           {
                               return !queue_.empty() | abort_; // 返回队列非空或者中断标志为真
                           });
        }
        if (abort_ == 1) // 如果中断标志为1
        {
            return -1; // 返回错误码
        }
        if (queue_.empty()) // 如果队列仍然为空
        {
            return -2; // 返回错误码
        }
        val = queue_.front(); // 获取队首元素
        queue_.pop(); // 弹出队首元素
        return 0; // 返回成功码
    }
    int Front(T &val)
    {
        std::lock_guard<std::mutex> lock(mutex_); // 使用互斥锁保护共享资源
        if (abort_ == 1) // 如果中断标志为1
        {
            return -1;
        }
        if (queue_.empty()) // 如果队列仍然为空
        {
            return -2;
        }
        val = queue_.front(); // 获取队首元素
        return 0;
    }

    int Size(T &val)
    {
        std::lock_guard<std::mutex> lock(mutex_); // 使用互斥锁保护共享资源
        queue_.size();  //获取队列大小
    }

private:
    int abort_ = 0; // 中断标志，默认为0
    std::mutex mutex_; // 互斥锁，保护共享资源
    std::condition_variable cond_; // 条件变量，用于线程等待和唤醒
    std::queue<T> queue_; // 队列容器，存储元素
};
#endif // QUEUE_H
