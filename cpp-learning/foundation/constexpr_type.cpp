/*
 * =======================================
 *  constexpr_type
 * =======================================
 */

static constexpr int size_a() {
    return 333;
}

static void constexpr_type() {
    constexpr int value_b = 3243;
    constexpr int value_c = value_b + 3;

    // 只有 size_a 是一个 constexpr 函数时才是一条正确的声明语句。
    constexpr int sz = size_a();
}

/**
 * constexpr 常量表达式：常量表达式是指值不会改变且在编译阶段就能计算结果的表达式。
 *
 * C++11 新标准规定，允许将变量声明为 constexpr 类型，以便编译器来校验变量的值是否为一个常量表达式。声明 constexpr 的
 * 变量一定是常量，且必需使用常量表达式。
 */
int main() {

}