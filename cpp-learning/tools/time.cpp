/*
 * =======================================
 * 日期时间
 * =======================================
 */

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <istream>
#include <sys/time.h>

using namespace std;

static void milliseconds() {
    // gettimeofday 是一个 POSIX 函数，用于获取当前时间，精度通常为微秒级。下面使用它来获取毫秒级的时间值。
    timeval tv{};
    gettimeofday(&tv, nullptr);
    const unsigned long long milliseconds1 =
        static_cast<unsigned long long>(tv.tv_sec) * 1000
        + static_cast<unsigned long long>(tv.tv_usec) / 1000;
    printf("Milliseconds since epoch: %llu\n", milliseconds1);


    // C++11 及以上版本提供了 std::chrono 库，可以用于高精度时间测量。
    // 可以使用 std::chrono::high_resolution_clock 来获取毫秒级的时间值。
    auto now = chrono::high_resolution_clock::now(); // 获取当前时间
    auto milliseconds2 = std::chrono::duration_cast<chrono::milliseconds>(
        now.time_since_epoch()
    ).count(); // 换为毫秒级
    cout << "Milliseconds since epoch: " << milliseconds2 << std::endl;
}

/**
 * 有四个与时间相关的类型：clock_t、time_t、size_t 和 tm。
 * 类型 clock_t、size_t 和 time_t 能够把系统时间和日期表示为某种整数。
 *
 * 结构类型 tm 把日期和时间以 C 结构的形式保存：
 *
 * @code
 *    struct tm {
 *         int tm_sec;   // 秒，正常范围从 0 到 59，但允许至 61
 *         int tm_min;   // 分，范围从 0 到 59
 *         int tm_hour;  // 小时，范围从 0 到 23
 *         int tm_mday;  // 一月中的第几天，范围从 1 到 31
 *         int tm_mon;   // 月，范围从 0 到 11
 *         int tm_year;  // 自 1900 年起的年数
 *         int tm_wday;  // 一周中的第几天，范围从 0 到 6，从星期日算起
 *         int tm_yday;  // 一年中的第几天，范围从 0 到 365，从 1 月 1 日算起
 *         int tm_isdst; // 夏令时
 *   }
 * @endcode
 */
static int time() {
    // time 函数返回系统的当前日历时间，自 1970 年 1 月 1 日以来经过的秒数。
    time_t raw_time;
    time(&raw_time);
    printf("time_t: %lld\n", raw_time);


    // localtime 函数返回一个指向表示本地时间的 tm 结构的指针。
    const tm* time_info = localtime(&raw_time);
    printf("time_info.tm_year: %d\n", time_info->tm_year);


    // asctime 函数返回一个指向字符串的指针，字符串包含了 time 所指向结构中存储的信息。
    printf("time: %s", asctime(time_info));


    /*
     * clock_t 是 C 标准库中的一个类型，用于表示处理器时间（processor time）。它通常用于测量程序运行时间。clock_t
     * 类型的值可以通过 clock 函数获取，并且可以通过 CLOCKS_PER_SEC 宏来转换为秒。
     */
    const clock_t start = clock(); // 记录开始时间
    for (volatile int i = 0; i < 100000000; i++) {
        // 模拟一些耗时操作
        // 空循环
    }
    const clock_t end = clock(); // 记录结束时间
    const double cpu_time_used = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    printf("Time elapsed: %f seconds\n", cpu_time_used);

    return EXIT_SUCCESS;
}

int main() {
    time();
    milliseconds();
}
