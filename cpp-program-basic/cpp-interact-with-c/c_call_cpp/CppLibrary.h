#ifndef INTERACTOR_CPPLIBRARY_H
#define INTERACTOR_CPPLIBRARY_H

// 1：C 调用 C++ 时，`c++` 代码需要照顾到 C，在 header 中使用 `extern "C"` 修饰包含函数声明，
//      目的就是告诉 `C++` 编译器其函数命名规则采用 C 的方式，这样 C 调用了 `C++` 函数，在链接时就能找得到。
// 2：声明 extern "C" 时，必须加上 __cplusplus 判断，否则会报错，不知为何。
#ifdef  __cplusplus
extern "C" {
#endif

int add(int a, int b);

#ifdef  __cplusplus
}
#endif

#endif
