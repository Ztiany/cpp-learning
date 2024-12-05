/*
 * =======================================
 *  decltype 和尾置返回类型声明
 * =======================================
 */

#include <iostream>

using namespace std;

// 1：使用 decltype 声明函数。
static int odd[] = {1, 3, 5, 7, 9};
static int even[] = {0, 2, 4, 6, 8};

// decltype 不负责把数组类型转换为对象的指针，所以返回值上需要加上*。
decltype(even)* arrPtr(const int i) {
    //返回一个指针，指针指向5个元素的数组
    return (i % 2) == 0 ? &even : &odd;
}

// 2：尾置返回类型是 C++11 中一种简化函数声明的函数声明方式，任何函数声明都可以使用尾置返回类型，
//    尾置返回类型跟在形参列表后面并一个以一个 `->` 符号开头。
static auto func(int i) -> int (*)[10]; //该函数返回一个指针，指针指向含有十个元素的 int 数组。

int main() {
    for (const int& i : *arrPtr(12)) {
        cout << i << std::endl;
    }
    return 0;
}
