#include <iostream>

// C++ 引用 C 的头文件时，加上 extern "C"
extern "C" {
#include "CLibrary.h"
}

/**
 * CPP 调用 C【情况1：c 头文件没有加上 extern "C"】
 */
int main() {

#ifdef  __cplusplus
    printf("running in the cpp\n");
#else
    printf("running in the c\n");
#endif

    int a = 100;
    int b = 300;
    int ret = add(a, b);
    std::cout << "cpp call c add result = " << ret << std::endl;
    return 0;
}