/*
 * =======================================
 * bitset（位集）
 * =======================================
 */

#include <cstdlib>
#include <iostream>
#include <bitset>

/**
 * 使用 bitset （位集）做标记处理，可以节约内存空间，因为标记只有`是/不是`两个状态，仅使用一个位即可表示，一个字节就可以表
 * 示八个标记，这个技术在 Android 中就有大量使用。
 */
int main() {
    std::bitset<32> flags("010101");

    std::cout << flags.test(0) << std::endl;
    std::cout << "sizeof(flags) " << sizeof(flags) << std::endl;

    return EXIT_SUCCESS;
}