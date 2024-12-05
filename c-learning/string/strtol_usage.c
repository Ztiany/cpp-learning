/*
 * =======================================
 *  strtol 的标准用法
 * =======================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

/**
 * `atoi` 这类函数使用上有问题——没有很好的方式处理转换失败的情况，当在 IDE 中使用这些函数，Clang-Tidy 会提示、诸如
 * 'atoi' used to convert a string to an integer value, but function will not report conversion
 * errors; consider using 'strtol' instead 这样的建议。即像 `atoi(), atof(), atol() 或是 atoll()` 这样的
 * 函数是不会设置 errno 的，如果结果无法计算的话，行为是 undefined。所以我们应该使用 glibc 后来提供的 strtol 类函数：
 *
 *          strtol() 会扫描参数 str 字符串，跳过前面的空白字符（例如空格，tab缩进等），直到遇上数字或正负符号才开始做
 *          转换，当转换过程中再次遇到非数字或字符串结束时('\0')结束转换，并将结果返回。
 *
 *              参数：str 待转换的字符串。
 *              参数：endptr 是出参，若 endptr 不为 NULL，则会将遇到的不符合条件而终止的字符指针由 endptr 传回；
 *                  若 endptr 为 NULL，则表示该参数无效，或不使用该参数。
 *              参考：base 表示进制
 *
 *          long strtol(const char *restrict str, char **restrict endptr, int base);
 */
int main() {
    char input[100];
    char* endptr;
    long val;

    printf("Enter a number: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    errno = 0; // 重置 errno 以检测错误
    val = strtol(input, &endptr, 10);

    // 检查转换是否成功
    if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) || (errno != 0 && val == 0)) {
        perror("strtol");
        return 1;
    }

    // 检查是否有非数字字符
    if (endptr == input) {
        fprintf(stderr, "No digits were found\n");
        return 1;
    }

    // 检查是否有额外的非数字字符
    while (*endptr != '\0') {
        if (*endptr != '\n' && *endptr != ' ') {
            fprintf(stderr, "Extra characters found: %s\n", endptr);
            return 1;
        }
        endptr++;
    }

    printf("Converted value: %ld\n", val);

    return 0;
}
