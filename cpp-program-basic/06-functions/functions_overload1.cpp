/*
 ============================================================================
 
 Author      : Ztiany
 Description : C++函数重载 1

 ============================================================================
 */

#include <iostream>

using namespace std;

// display_v
void display() {
    cout << "display()" << endl;
}

// display_i
void display(int a) {
    cout << "display(int) - " << a << endl;
}

// display_l
void display(long a) {
    cout << "display(long) - " << a << endl;
}

// display_d
void display(double a) {
    cout << "display(double) - " << a << endl;
}

// Debug 模式：很多调试信息，生成的可执行文件比较臃肿。
// Release 模式：去除调试信息，生成的可执行文件比较精简、高效。
int main() {
    display();
    display(10);
    display(10L);
    display(10.0);
    return 0;
}