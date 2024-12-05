/*
 * =======================================
 *  使用使用可移植的类型来提高程序的可移植性
 * =======================================
 */

#include <cstdlib>
#include <cstdint>

int main() {
    int32_t int_a = 3;
    int32_t int_b = 3;

    int32_t* const pa = &int_a;
    int32_t const* pb = &int_a;
    pb = &int_b;

    return EXIT_SUCCESS;
}
