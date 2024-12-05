/*
 * =======================================
 * 栈解旋
 * =======================================
 */

#include <iostream>
#include <utility>

using namespace std;

class Person {
    string name;

public:
    explicit Person(string _name): name(std::move(_name)) {
        cout << name << "-对象构建!" << endl;
    }

    ~Person() {
        cout << name << "-对象析构!" << endl;
    }
};

static int divide(const int x, const int y) {
    Person p1("p1"), p2("p2");

    if (y == 0) {
        throw y;
    }

    return x / y;
}

/**
 * 异常被抛出后，从进入 try 块起，到异常被抛掷前，这期间在栈上构造的所有对象，都会被自动析构。
 * 析构的顺序与构造的顺序相反，这一过程称为栈的解旋（unwinding）。
 */
int main() {
    try {
        divide(10, 0);
    } catch (int e) {
        cout << "异常捕获！" << endl;
    }
    return 0;
}
