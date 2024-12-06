/*
 * =======================================
 *  C++ 11 Threading
 * =======================================
 */

#include <cstdio>
#include <thread>

using namespace std;

static void cppThreadSample() {
    // 线程，有时被称为轻量进程，是程序执行的最小单元。
    thread threadA([] {
        // 暂停 1 秒（1000毫秒）
        this_thread::sleep_for(chrono::seconds(2));
        printf("Hello from Thread.\n");
    });

    // 等待线程结束再继续执行
    threadA.join();
}

int main() {
    cppThreadSample();
}