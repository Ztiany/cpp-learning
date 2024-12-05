/*
* =======================================
 *  拷贝构造函数
 * =======================================
 */

#include "copy_constructor.h"

using namespace std;

// 如果这里不使用引用，则会造成 line 再次被拷贝。
static void display(Line& obj) {
    cout << "line size: " << obj.getLength() << endl;
}

int main() {
    Line line1(10);

    // 这里也调用了拷贝构造函数
    Line line2 = line1;

    Line line3(1);
    // 这里调用拷贝赋值操作符
    line3 = line1;

    display(line1);
    display(line2);
}
