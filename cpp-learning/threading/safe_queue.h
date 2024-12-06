#ifndef CPLUSPLUS_PROGRAM_POSIX_PTHREAD_H
#define CPLUSPLUS_PROGRAM_POSIX_PTHREAD_H

#include <queue>
#include <pthread.h>

class ThreadMutexParams {
public:
    std::queue<int>* queue_;
    pthread_mutex_t* mutex_;

    ThreadMutexParams(
        std::queue<int>* queue,
        pthread_mutex_t* mutex
    ) : queue_(queue), mutex_(mutex) {}
};

/** 一个阻塞队列实现  */
template <typename T>
class SafeQueue {
    std::queue<T> q;

    pthread_mutex_t mutex;
    pthread_cond_t cond;

public:
    /*
     * 在 C++ 中，如果一个类包含需要动态初始化的非平凡类型成员变量（如 pthread_mutex_t 和 pthread_cond_t），而这些
     * 成员变量没有在类的构造函数中被显式初始化，编译器会发出警告，因为这些类型不是 C++ 的 POD（Plain Old Data）类型，
     * 它们的默认初始化（即置零）是未定义行为。
     *
     * 为了解决这个问题，您可以在类的构造函数中使用 std::memset 来显式初始化这些成员变量，或者使用 C++11 的
     * std::mutex 和 std::condition_variable 来替代 pthread_mutex_t 和 pthread_cond_t，因为它们
     * 提供了 C++ 风格的线程同步原语，并且可以被直接初始化。
     *
     * 下面是使用 std::memset 来显式初始化这些成员变量。
     */
    SafeQueue(): mutex(PTHREAD_MUTEX_INITIALIZER), cond(PTHREAD_COND_INITIALIZER) {
        pthread_mutex_init(&mutex, nullptr);
        pthread_cond_init(&cond, nullptr);
    }

    ~SafeQueue() {
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond);
    }

    /**
     * 生产：加入数据
     */
    void push(T t) {
        pthread_mutex_lock(&mutex);
        q.push(t);

        // notify：由系统唤醒一个线程（无法控制唤醒哪个线程）。
        //pthread_cond_signal(&cond);

        // 广播通知所有等待的线程
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    }

    /**
     * 消费：取数据
     */
    void pop(T& t) {
        pthread_mutex_lock(&mutex);
        // 错误的做法，因为线程可能被系统意外唤醒。
        /*if (!q.empty()) {
            t = q.front();
            q.pop();
        }*/

        // 等待其他地方唤醒，可能被系统意外唤醒，因此要用 while， queue 为空则一直等待，直到下一次 push 生产出数据。
        while (q.empty()) {
            // 挂起 释放锁
            pthread_cond_wait(&cond, &mutex);
        }
        t = q.front();
        q.pop();

        pthread_mutex_unlock(&mutex);
    }
};

#endif
