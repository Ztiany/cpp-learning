/*
 * =======================================
 *  constexpr/inline
 * =======================================
 */


/**
 * constexpr 函数可用于常量表达式，执行初始化任务时，编译器把对 constexpr 函数的调用替换成结果值，为了能在编译过程中展
 * 开，constexpr 函数被隐式的声明为内联函数，声明 constexpr 函数有如下规则。
 *
 *  - 函数的返回值和所有形参类型都必须是字面值类型。
 *  - 函数有且只有一条 return 语句。
 */
static constexpr int length() {
    return 3;
}

static inline int add(const int a, const int b) {
    return a + b;
}

/**
 * 将内联函数和 constexpr 函数放在头文件中：内联函数和 constexpr 函数与其他函数不一致，通常应该在头文件中定义，编译器想
 * 要展开内联函数和 constexpr 函数，仅有函数原型是不够的，还需要函数定义，而内联函数和 constexpr 函数可能在多个地方被调
 * 用。内联函数和 constexpr 函数可以多次定义，只要保证定义完全一致。
 *
 * 因此：把 inline 函数的定义放在头文件中，可以确保在调用函数时所使用的定义是相同的，并且保证在调用点该函数的定义对编译器可见。
 */
int main() {
    int a = length();
    return 0;
}
