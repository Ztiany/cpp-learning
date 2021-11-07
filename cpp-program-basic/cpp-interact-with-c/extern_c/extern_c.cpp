/*
 ============================================================================
 
 Author      : Ztiany
 Description : extern c 的作用

 ============================================================================
 */

#include <cstdlib>

/*
 * 被extern "C"修饰的代码会按照C语言的方式去编译，导致下面两个重载的 C++ 函数编译失败。
 */
extern "C" int add(int a) {
    return a + 10;
}

extern "C" int add(int a, int b) {
    return a + b;
}

int main() {

    return EXIT_SUCCESS;
}
