/*
 * =======================================
 *  字符串
 * =======================================
 */

#include <stdlib.h>
#include <errno.h>
#include <limits.h>
// C 标准 `<string.h>`头文件定义了字符串常用函数。
#include <string.h>
// sprintf() 函数声明在 stdio.h 中，该函数和 printf() 类似，但是它是把数据写入字符串，而不是打印在显示器上。因此该函数
// 可以把多个元素组合成一个字符串。
#include <stdio.h>
#include <wchar.h>

/**
 * 定义字符串。
 */
static void define_string() {
    const char c_arr[] = {'a', 'b', '\0'};
    const char* str1 = "hello";
    // "abc""ddd""zz" = "abcdddzz";
    const char* str2 = "abc""ddd""zz";

    printf("c = %o\n", c_arr); // 以八进制形式输出数组首地址
    printf("c = %s\n", c_arr); // 以字符串的形式输出字符数组

    // 宽字符串：
    //      使用 char 数组，与文件编码有关，比如文件是 UTF-8 编码的，那么存的就是中文的 UTF-8 编码，
    //      一个 UTF-8 编码要多个字符，因此这里这个数组长度为 15.
    const char string_zh[] = "你好，中国";
    //      使用 wchar_t 存的都是码点，一个宽字符可以存储一个码点，数组长度为 5【可以通过断点调试查看内存信息】
    const wchar_t ws_zh[] = L"你好，中国";
    printf("length of string_zh = %lu\n", strlen(string_zh));
    printf("length of ws_zh = %lu\n", wcslen(ws_zh));
}

/**
 * 获取字符串长度。
 */
static void string_length() {
    const char c_arr[] = "我是中国人";
    const size_t length = strlen(c_arr);
    printf("c_arr 的长度是：%zd\n", length);
}

/**
 * 字符串比较。
 */
static void string_compare() {
    const char c_arr1[] = "abcd";
    const char c_arr2[] = "ABCD";
    const int result = strcmp(c_arr1, c_arr2);
    printf("字符串比较结果：%d\n", result);
}

/**
 * 字符串拷贝。
 */
static void string_copy() {
    const char c_arr1[] = "abcd";
    const char c_arr2[] = "ABCD";
    strcpy(c_arr1, c_arr2);
    printf("复制后的字符串：%s\n", c_arr1);
}

/**
 * 字符串转换为数字。
 */
static void string_to_number() {
    const char s_number[] = "100";

    /*
     * 'atoi' used to convert a string to an integer value, but function will not report conversion
     * errors; consider using 'strtol' instead.
     */
    const int num1 = atoi(s_number);
    printf("使用 atoi 转为数字：%d\n", num1);

    errno = 0; // 重置 errno 以检测错误
    const int num2 = strtol(s_number, NULL, 10);

    // 检查转换是否成功
    if ((errno == ERANGE && (num2 == LONG_MAX || num2 == LONG_MIN)) || (errno != 0 && num2 == 0)) {
        perror("strtol");
    } else {
        printf("使用 strtol 转为数字：%d\n", num2);
    }
}

/**
 * 遍历字符串。
 */
static void traverse_string() {
    const char* str = "Hello String";
    // *str 与 *str!='\0' 其实是一样的意思，当 *str=='\0' 时，其整型值就是 0，也就是 false。
    while (*str) {
        putchar(*str);
        str++;
    }
    putchar('\n');
}

/**
 * sprintf 用于将格式化的数据写入字符串缓冲区。
 */
static void string_format() {
    char buffer[100];
    int a = 42;
    double b = 3.14159;
    char str[] = "Hello, World!";

    // 使用 sprintf 格式化数据并写入 buffer。
    sprintf(buffer, "Integer: %d, Double: %.2f, String: %s", a, b, str);

    // 打印格式化后的字符串
    printf("%s\n", buffer);
}

int main() {
    define_string();
    string_length();
    string_compare();
    string_copy();
    string_to_number();
    traverse_string();
    string_format();
    return 0;
}
