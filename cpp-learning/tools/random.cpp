/*
 * =======================================
 * 随机数
 * =======================================
 */

#include <iostream>
#include <ctime>
// C++11 的随机数库
#include <random>

using namespace std;

/**
 * C 风格随机数。
 */
static void random1() {
    /*
     * 设置种子：使用 srand(static_cast<unsigned>(time(nullptr))) 通过当前时间设置随机数种子是传统 C 风格的随机
     * 数生成方法，但它存在以下问题：
     *
     *  - 可预测性：时间 (time(nullptr)) 是一个可预测的值，特别是在短时间内多次调用 srand，
     *    可能会导致生成的随机数序列重复。
     *  - 不安全性：在某些需要高随机性的场景（如密码学应用）中，这种方法很容易被攻击者推测。
     *
     * 补充：srand 来自 cstdlib 头文件（在 C 语言中是 stdlib.h）。srand 函数用于设置随机数生成器的种子（seed）。
     *      srand 是 "seed random" 的缩写，表示设置随机数生成器的种子。
     */
    srand(static_cast<unsigned>(time(nullptr)));

    /* 生成 10 个随机数 */
    for (int i = 0; i < 10; i++) {
        // 生成实际的随机数：rand() 是 C 风格的随机数生成函数，它的随机性较低。
        // Rand() has limited randomness; use C++11 random library instead.
        cout << "bad randomNumber:  " << rand() << endl;
    }
}

/**
 * 使用 C++11 标准引入的 <random> 库，提供高质量的随机数生成功能。
 */
static void random2() {
    // 设置随机数生成器和分布
    std::random_device rd; // 硬件随机数种子
    std::mt19937 gen(rd()); // Mersenne Twister 引擎
    std::uniform_int_distribution distrib(1, 100); // 定义分布范围 [1, 100]

    /* 生成 10 个随机数 */
    for (int i = 0; i < 10; i++) {
        // 生成实际的随机数
        std::cout << "good randomNumber: " << distrib(gen) << std::endl;
    }
}

int main() {
    random1();
    random2();
}
