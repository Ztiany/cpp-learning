/*
 * =======================================
 * 显式类型转换
 * =======================================
 */

#include <cstdlib>
#include <iostream>

using namespace std;

void receiveA(int* pI) {}

int main() {
    // static_cast
    int i1 = 4;
    int i2 = 5;
    double slope = static_cast<double>(i1) / i2;

    void* pSlope = &i1; // 任何非常量对象的地址都能存入 void*
    double* slope2 = static_cast<double*>(pSlope);


    // const_cast 用于去除 const 属性。
    int i3 = 333;
    const int* p_ci3 = &i3;

    // 通过 const_cast 去除 const 属性。
    int* p_i3 = const_cast<int*>(p_ci3);
    // 由于 i3 本身不是常量，所以这里的写是合法的。
    *p_i3 = 100;

    cout << "*p_i3 = " << *p_i3 << endl; // 始终为：100
    cout << "i3 = " << i3 << endl; // 如果 i3 是 const 的，那么无法修改 i3 的值，i3 始终未为 333

    // 应用场景：函数接收非 const 参数
    receiveA(const_cast<int*>(p_ci3));
    return EXIT_SUCCESS;
}
