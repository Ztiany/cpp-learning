/*
 * =======================================
 *  线程自动化管理封装
 * =======================================
 */

#ifndef CPLUSPLUS_PROGRAM_THREADLOCK_H
#define CPLUSPLUS_PROGRAM_THREADLOCK_H

#include <mutex>
#include <pthread.h>
#include <cassert>
#include <sys/file.h>

class ThreadLock {
    pthread_mutex_t m_lock;

public:
    ThreadLock() {
        // 初始化锁的属性
        pthread_mutexattr_t mutexattr;
        pthread_mutexattr_init(&mutexattr);
        pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE);
        // 初始化锁
        pthread_mutex_init(&m_lock, &mutexattr);
        // 释放资源
        pthread_mutexattr_destroy(&mutexattr);
    }

    ~ThreadLock() {
        pthread_mutex_destroy(&m_lock);
    }

    void lock() {
        if (const auto result = pthread_mutex_lock(&m_lock); result != 0) {
            printf("ThreadLock lock error\n");
        }
    }

    bool try_lock() {
        const auto result = pthread_mutex_trylock(&m_lock);
        return result == 0;
    }

    void unlock() {
        if (const auto result = pthread_mutex_unlock(&m_lock); result != 0) {
            printf("ThreadLock unlock error\n");
        }
    }
};

/**
* 利用 RAII 实现的锁 ScopedLock。
*/
template <typename T>
class ScopedLock {
    T* m_lock;

public:
    // 禁止使用编译器默认生成的拷贝构造函数
    ScopedLock(const ScopedLock& other) = delete;

    // 禁止使用编译器默认生成的拷贝赋值操作符
    ScopedLock& operator=(const ScopedLock& other) = delete;

    explicit ScopedLock(T* l_lock) : m_lock(l_lock) {
        assert(m_lock);
        lock();
    }

    ~ScopedLock() {
        unlock();
    }

    void lock() {
        if (m_lock) {
            m_lock->lock();
        }
    }

    bool try_lock() {
        if (m_lock) {
            return m_lock->try_lock();
        }
        return false;
    }

    void unlock() {
        if (m_lock) {
            m_lock->unlock();
        }
    }
};

/**
 * decltype：推断变量类型；__scopedLock##counter(&lock)：## 为连接符。
 */
#define __SCOPEDLOCK(lock, counter) ScopedLock<decltype(lock)> __scopedLock##counter(&lock)

#define _SCOPEDLOCK(lock, counter) __SCOPEDLOCK(lock, counter)

/**
 * __COUNTER__ 是一个预定义的宏，它在每个编译单元中初始值为 0，并且每次使用时都会自动增加 1。这意味着每次调用
 * SCOPEDLOCK(lock) 时，都会生成一个唯一的计数器，从而确保每次创建的作用域锁都有一个唯一的名称。
 */
#define SCOPEDLOCK(lock) _SCOPEDLOCK(lock, __COUNTER__)

#endif