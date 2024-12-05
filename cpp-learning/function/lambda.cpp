/*
 * =======================================
 *  Lambda 表达式
 * =======================================
 */

#include <iostream>

/**
 * C++11 提供了对匿名函数的支持，称为 Lambda 表达式。Lambda 表达式把函数看作对象。Lambda 表达式可以像对象一样使用，
 * 比如可以将它们赋给变量和作为参数传递，还可以像函数一样对其求值。
 */
int main() {
    auto compare = [](int x, int y) {
        return x < y;
    };

    std::cout << "compare(1, 2) is: " << compare(1, 2) << std::endl;
}
