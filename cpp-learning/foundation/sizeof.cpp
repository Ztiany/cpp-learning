/*
 * =======================================
 * sizeof 表达式
 * =======================================
 */

#include <iostream>
#include <vector>

using namespace std;

/**
 * size：
 *
 * - 对引用类型执行 sizeof 运算得到的是引用类型所占内存字节数。
 * - 对指针类型执行 sizeof 运算得到的是指针所占内存字节数，在固定的系统中，这是固定的。
 * - 对数组类型执行 sizeof 运算得到的是数组所占总内存的字节数。
 */
int main() {
    // char 或 char 类型为 1。
    cout << sizeof(char) << endl;

    /*
     * vector 是一个模板类，它是一个动态数组，可以自动调整大小。vector 的大小由其元素的数量和每个元素的大小决定。但是，
     * sizeof(vector<int>) 给出的是 vector 对象本身的大小，而不是它所包含的元素的总大小。
     *
     * vector对象通常包含三个指针：
     *
     *  - 一个指向数组开始的指针。
     *  - 一个指向数组当前结束的指针。
     *  - 一个指向数组分配的内存结束的指针。
     *
     *  在 64 位系统中，每个指针的大小是 8 字节。因此，vector 对象本身的大小是 3 个指针的大小之和。
     */
    cout << sizeof(vector<int>) << endl;

    //对于 string，sizeof 只返回该类型的固定大小，32。
    cout << sizeof(string) << endl;
    return EXIT_SUCCESS;
}
