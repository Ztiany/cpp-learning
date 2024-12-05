/*
 * =======================================
 *  可移植的数据类型
 * =======================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// inttypes.h 引入于 C99 标准，提供了各种位宽的整数类型输入输出时的转换标志宏。
#include <inttypes.h>
// stdint.h 引入于 C99 的标准，主要用于统一跨平台数据定义。
#include <stdint.h>
// wchar.h 引入于 C95 的标准，扩展多字节和宽字符工具。
#include <wchar.h>
// wctype.h 引入于 C95 的标准，用来确定包含于宽字符数据中的类型的函数。
#include <wctype.h>

/**
 * <inttypes.h> 是 C99 标准引入的头文件，主要提供了对各种位宽整数类型的输入输出时的转换标志宏。它允许你以可移植的方式进
 * 行整数格式化输出，比如 int8_t, int32_t, int64_t 等类型。这样，程序在不同的平台和编译器中也能进行一致的格式化输出。
 *
 * 常用宏：
 *
 *  - PRId8, PRIu32, PRIx64 等，用于指定整数的格式。
 *  - SCNd8, SCNu32, SCNx64 等，用于输入时的格式化。
 */
static void inttypes(void) {
    int32_t i32 = 123456;
    int64_t i64 = 9876543210;

    printf("int32_t: %" PRId32 "\n", i32); // 使用 PRId32 宏输出 32 位整数
    printf("int64_t: %" PRId64 "\n", i64); // 使用 PRId64 宏输出 64 位整数
}

/**
 * <stdint.h> 也是 C99 标准引入的头文件，提供了跨平台的整数类型定义，确保在不同的系统和编译器中具有相同大小的整数类型。它
 * 定义了一组固定大小的整数类型，例如 int8_t, int16_t, int32_t, int64_t 等，同时也提供了无符号版本（如 uint32_t）。
 *
 * 常用类型：
 *
 * - int8_t, int16_t, int32_t, int64_t（带符号整数）
 * - uint8_t, uint16_t, uint32_t, uint64_t（无符号整数）
 * - intptr_t, uintptr_t（用于指针的整数类型）
 */
static void stdint(void) {
    const int32_t a = -1000;
    const uint16_t b = 50000;

    printf("int32_t: %" PRId32 "\n", a);
    printf("uint16_t: %" PRIu16 "\n", b);
}

/**
 * <wchar.h> 是 C95 标准引入的头文件，提供了对宽字符和宽字符字符串的操作支持。它定义了 wchar_t 类型，适用于处理多字节字
 * 符集（如 UTF-16、UTF-32）中的字符。你可以使用宽字符类型来处理 Unicode 字符串，特别是在国际化应用中。
 *
 * 常用函数：
 *
 * - wchar_t: 宽字符类型
 * - wprintf(): 用于输出宽字符字符串
 * - wcslen(): 获取宽字符字符串的长度
 * - fgetwc(), fputwc(): 输入输出宽字符
 */
static void wchar(void) {
    // L 告诉编译器该字符串按宽字符保存，即每个字符占用 2 个字节。
    const wchar_t wc_zhong = L'中';
    const wchar_t* ws_zhong = L"中";
    const char* zhong_code = "\u4e2d";
    printf("wcslen(L'中') = %llu\n", wcslen(ws_zhong));
    printf("sizeof(L'中') = %zd\n", sizeof(wc_zhong));
    printf("sizeof(L'\u4e2d') = %zd\n", strlen(zhong_code));
}

/**
 * <wctype.h> 是 C95 标准引入的头文件，提供了用于处理宽字符的分类和测试函数。它可以检查一个宽字符是否是某个特定类别，如
 * 字母、数字、空白字符等。这对于处理宽字符字符串中的字符类型非常有用。
 *
 * 常用函数：
 *
 * - iswalpha(), iswdigit(), iswspace(): 检查字符是否为字母、数字或空白字符
 * - towlower(), towupper(): 转换宽字符的大小写
 */
static void wide_char_type(void) {
    const wchar_t ch = L'A';
    if (iswalpha(ch)) {
        printf("%lc 是字母\n", ch);
    }
    printf("towlower(ch): %lc\n", towlower(ch));
}

int main() {
    inttypes();
    stdint();
    wchar();
    wide_char_type();
    return EXIT_SUCCESS;
}