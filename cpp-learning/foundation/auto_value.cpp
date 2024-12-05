/*
 * =======================================
 *  auto
 * =======================================
 */

int main() {
    int value_a = 3, value_b = 4;
    // 编译器推断出 value_c 的类型是 int 类型
    auto value_c = value_a + value_b;
    // 编译器推断出 value_c 的类型是 int 类型指针
    auto pA = &value_a;
    int* pB = pA;
    int value_d = value_c;
}
