/*
 * =======================================
 *  动态对象
 * =======================================
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include "dynamic_object.h"

using namespace std;

int main() {
    // 基本类型
    const int* pi1 = new int; // pi 指向一个未知的 int 值
    const int* pi2 = new int(1024); // pi 指向一个 int，值为 1024
    const int* pi3 = new int(); // pi 指向初始化值为 0 的 int
    cout << "pi1 = " << *pi1 << "   pi2 = " << *pi2 << "   pi3 = " << *pi3 << endl;
    delete pi1;
    delete pi2;
    delete pi3;

    // 内置类类型
    const string* ps1 = new string(10, '9'); // *ps 为 "9999999999"
    const string* ps2 = new string(); // 空字符串
    cout << "ps1 = " << *ps1 << endl;
    cout << "ps2 = " << *ps2 << endl;
    delete (ps1);
    delete (ps2);

    // 类类型
    const DynamicObject2* dynamicObject = new DynamicObject2(12, 24);
    cout << "dynamicObject.total = " << dynamicObject->getTotal() << endl;
    delete (dynamicObject);

    // 动态数组

    // 1 个参数，要求 DynamicObject1 的构造函数不能是 explicit 修饰的。
    const DynamicObject1* dynamicObject2Arr = new DynamicObject1[5]{1, 2, 3, 4, 5};
    cout << "dynamicObject1Arr[1].total = " << (dynamicObject2Arr + 1)->getTotal() << endl;
    delete[] dynamicObject2Arr;

    // 2 个参数
    const DynamicObject2* dynamicObjectArr = new DynamicObject2[2]{
        DynamicObject2(3, 3),
        DynamicObject2(4, 4)
    };
    cout << "dynamicObjectArr2[1].total = " << (dynamicObjectArr + 1)->getTotal() << endl;
    delete[] dynamicObjectArr;

    // 其实使用 vector 更加合适
    const vector doVector(100, DynamicObject2(2, 3));
    for (const DynamicObject2& obj : doVector) {
        cout << "obj.total = " << obj.getTotal() << endl;
    }

    return EXIT_SUCCESS;
}
