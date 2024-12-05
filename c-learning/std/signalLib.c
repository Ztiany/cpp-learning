/*
 * =======================================
 *  signal.h
 * =======================================
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

static void sig_handler(const int signum) {
    printf("capture signal %d and break...\n", signum);
    exit(1);
}

/**
 * signal.h 是 C 标准函数库中的信号处理部分，定义了程序执行时如何处理不同的信号。信号用作进程间通信，报告异常行为（如除
 * 零）、用户的一些按键组合（如同时按下 Ctrl与 C 键，产生信号 SIGINT）。
 *
 * 在 Linux 内的信号处理函数中，有 #define SIG_DFL ((void(*)(int))0) 和 #define SIG_IGN ((void(*)(int))1)
 * 两个宏定义。它们是预定义的信号 handler，分别表示对捕获的信号采取忽略操作或者默认操作。
 */
int main(void) {
    // 设置一个函数来处理信号，即带有 sig 参数的信号处理程序，可以理解为回调。
    // 下面函数表示当发生 SIGINT 信号时，调用 sig_handler 函数。Ctrl+C 可以发送 SIGINT 信号。
    if (signal(SIGINT, sig_handler) == SIG_ERR) {
        fputs("An error occurred while setting a signal handler.\n", stderr);
        return EXIT_FAILURE;
    }

    int a = 1;
    while (1) {
        printf("start sleep 1 second...\n");
        a++;
        if (a == 5) {
            //raise 用于发送一个信号
            int ret = raise(SIGINT);
            if (ret != 0) {
                fputs("Error raising the signal.\n", stderr);
                return EXIT_FAILURE;
            }
        }
        sleep(1);
    }

    return EXIT_SUCCESS;
}
