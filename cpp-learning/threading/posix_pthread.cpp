/*
 * =======================================
 *  Posix Threading
 * =======================================
 */

#include <cstdlib>
#include <pthread.h>
#include <mutex>
#include <iostream>
#include <thread>
#include <unistd.h>
#include "safe_queue.h"
#include "thread_lock.h"

using namespace std;

static void* task1(void* args) {
    std::cout << "Thread is going to sleep for 3 seconds." << std::endl;
    usleep(3000 * 1000);
    std::cout << "Thread woke up." << std::endl;

    char name[16];
    pthread_getname_np(pthread_self(), name, sizeof(name));
    std::cout << "Thread name: " << name << std::endl;

    static int result = 100;
    cout << "task1 self = " << pthread_self() << " running" << endl;
    return &result;
}

// 示例 1：创建线程
static void pthreadSample() {
    // 准备线程属性：
    // 出参，获取线程 id。
    // 入参，线程的属性，可以传 null。
    pthread_attr_t pthreadAttr;
    pthread_attr_init(&pthreadAttr);
    // 设置为分离线程，此时 join 有效。
    pthread_attr_setdetachstate(&pthreadAttr, PTHREAD_CREATE_JOINABLE);
    // 设置调度策略
    pthread_attr_setschedpolicy(&pthreadAttr, SCHED_FIFO);
    // 设置优先级
    sched_param schedParam{};
    schedParam.sched_priority = sched_get_priority_max(SCHED_FIFO);
    cout << "max priority = " << schedParam.sched_priority << endl;
    pthread_attr_setschedparam(&pthreadAttr, &schedParam);

    // 创建线程
    pthread_t pid;
    pthread_create(&pid, &pthreadAttr, task1, nullptr);

    pthread_setname_np(pid, "pthreadSample");

    // 销毁属性
    pthread_attr_destroy(&pthreadAttr);

    // 等待线程结束
    int* result = nullptr;
    pthread_join(pid, reinterpret_cast<void**>(&result));

    cout << "pthreadSample task return = " << *result << endl;
    cout << "pthreadSample end self = " << pthread_self() << endl;
}

static void* task2(void* args) {
    const auto* params = static_cast<ThreadMutexParams*>(args);

    pthread_mutex_lock(params->mutex_);

    if (!params->queue_->empty()) {
        cout << "threadSafeTask " << " getElement " << params->queue_->front() << endl;
        params->queue_->pop();
    } else {
        cout << "threadSafeTask  " << " getElement " << "nothing" << endl;
    }

    pthread_mutex_unlock(params->mutex_);

    return nullptr;
}

// 示例 2：线程安全示例
static void threadSafeSample() {
    queue<int> queue;

    for (int i = 0; i < 5; ++i) {
        queue.push(i);
    }

    pthread_mutex_t pthreadMutex;
    pthread_mutex_init(&pthreadMutex, nullptr);

    ThreadMutexParams threadMutexParams(&queue, &pthreadMutex);

    for (int i = 0; i < 5; ++i) {
        pthread_t pid;
        pthread_create(&pid, nullptr, task2, &threadMutexParams);
    }

    pthread_mutex_destroy(&pthreadMutex);

    // 等待 3 秒
    usleep(3000 * 1000);
}

void* getTask(void* args) {
    printf("getTask running\n");
    auto* sq = static_cast<SafeQueue<int>*>(args);
    while (true) {
        int i = -1;
        // 如果队列中没有数据就卡在这里
        sq->pop(i);
        if (i == -100/*100 为推出标志*/) {
            break;
        }
        cout << "get:" << i << endl;
    }
    return nullptr;
}

void* putTask(void* args) {
    printf("putTask running\n");
    auto* sq = static_cast<SafeQueue<int>*>(args);
    while (true) {
        int i;
        // 将用户输入 给 i保存
        cin >> i;
        sq->push(i);
        if (i == -100/*100 为推出标志*/) {
            break;
        }
        if (cin.fail()) {
            // 错误的输入
            cerr << "bad data, try again" << endl; // 警告用户
            cin.clear(iostream::goodbit); //重置状态
            cin.ignore(); //清除缓冲区，否则错误的输入一直在缓冲区中
            continue; //继续
        }
    }
    return nullptr;
}

// 示例 3：线程安全示例-生产者与消费者模型
void safeQueueSample() {
    SafeQueue<int> sq{};
    pthread_t pidGet;
    pthread_t pidPut;
    pthread_create(&pidGet, nullptr, getTask, &sq);
    pthread_create(&pidPut, nullptr, putTask, &sq);
    pthread_join(pidGet, nullptr);
    pthread_join(pidPut, nullptr);
}

ThreadLock threadLock;
int value = 0;

void* lockAutoManagementTask(void* args) {
    // 调用 SCOPEDLOCK 宏，相当于整个函数都被线程独占。
    SCOPEDLOCK(threadLock);
    const pthread_t pid = *static_cast<pthread_t*>(args);
    for (int i = 0; i < 10; ++i) {
        value++;
        cout << "thread " << pid << " running" << endl;
    }
    return nullptr;
}

// 示例 4：线程锁自动化管理
void lockAutoManagementSample() {
    pthread_t p_arr[100];

    for (pthread_t& i : p_arr) {
        pthread_create(&i, nullptr, lockAutoManagementTask, &i);
    }

    for (unsigned long long i : p_arr) {
        pthread_join(i, nullptr);
    }
    cout << "value = " << value << endl;
}

int main() {
    // pthreadSample();
    threadSafeSample();
    // safeQueueSample();
    // lockAutoManagementSample();
    return EXIT_SUCCESS;
}