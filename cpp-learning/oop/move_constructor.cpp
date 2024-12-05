/*
 * =======================================
 *  移动拷贝构造函数
 * =======================================
 */

#include <vector>
#include <cstdlib>
#include <iostream>
#include "move_constructor.h"

using namespace std;

void sample1() {
    int i = 42;
    int& r = i;
    //int &&rr = i; 错误
    //int &r2 = i * 24; 错误
    const int& r3 = i * 24;
    int&& rr2 = i * 24;
}

void sample2() {
    int vi = 3;
    int&& rri = std::move(vi);
    int&& rri2 = 3;
    const int& vi2 = rri2;
    int&& rri3 = std::move(rri);
    constexpr int vi3 = 3;
    constexpr int vi4 = 3;
    cout << "address  rri = " << &rri << endl;
    cout << "address   vi = " << &vi << endl;
    cout << "address rri3 = " << &rri3 << endl;
    cout << "address rri2 = " << &rri2 << endl;
    cout << "address  vi2 = " << &vi2 << endl;
    cout << "address  vi3 = " << &vi3 << endl;
    cout << "address  vi4 = " << &vi4 << endl;
}

void sample3() {
    MoveClass moveClass1("a");
    // 不会创建一个新的对象，moveClass2 也指向 moveClass1 所指向的对象。
    const MoveClass& moveClass2 = moveClass1;

    MoveClass moveClass3 = moveClass1;
    MoveClass moveClass4{std::move(MoveClass("b"))};

    MoveClass moveClass5(MoveClass("c"));
}

void sample4() {
    vector<MoveClass> vector1;
    vector1.push_back(MoveClass("mc1"));
}

void sample5() {
    MoveClass moveClass1("A");
    MoveClass moveClass2("B");
    moveClass1 = moveClass2; // moveClass2 是左值，使用拷贝操作。
    moveClass1 = MoveClass("C"); // 使用移动操作，MoveClass("C") 是右值。
}

// 参数：-Og -fno-elide-constructors
int main() {
    cout << "------ sample 1 ------" << endl;
    sample1();
    cout << "------ sample 2 ------" << endl;
    sample2();
    cout << "------ sample 3 ------" << endl;
    sample3();
    cout << "------ sample 4 ------" << endl;
    sample4();
    cout << "------ sample 5 ------" << endl;
    sample5();
    return EXIT_SUCCESS;
}
