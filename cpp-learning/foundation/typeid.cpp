/*
 * =======================================
 * typeid
 * =======================================
 */

#include <cstdlib>
#include <iostream>

using namespace std;

/**
 * typeid 用于在运行时获知变量类型名称，使用方式 `typeid(变量).name()`。
 *
 * typeid 类似 sizeof，是一个操作符而不是函数。typeid 操作符的返回结果是名为 `type_info` 的标准库类型的对象的引用。
 */
int main() {

    int i = 1;
    long l = 1;

    cout << "typeid(i) = " << typeid(i).name() << endl;
    cout << "typeid(l) = " << typeid(l).name() << endl;

    if (typeid(i) == typeid(int)) {
        cout << "type of i is int" << endl;
    }

    return EXIT_SUCCESS;
}
