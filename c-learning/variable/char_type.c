/*
* =======================================
 *  字符判断
 * =======================================
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * ctype.h 是 C 标准库中的一个头文件，它提供了一组用于字符分类和转换的函数。这些函数可以帮助你检查字符的类型（如字母、数
 * 字、空白字符等），并进行字符的大小写转换。
 *
 */
int main() {
    const char ch = 'A';

    // 检查字符是否是字母
    if (isalpha(ch)) {
        printf("%c is an alphabetic character.\n", ch);
    }

    // 检查字符是否是数字
    if (isdigit(ch)) {
        printf("%c is a digit.\n", ch);
    }

    // 检查字符是否是小写字母
    if (islower(ch)) {
        printf("%c is a lowercase letter.\n", ch);
    }

    // 检查字符是否是大写字母
    if (isupper(ch)) {
        printf("%c is an uppercase letter.\n", ch);
    }

    // 将字符转换为小写
    const char lower_ch = tolower(ch);
    printf("Lowercase of %c is %c.\n", ch, lower_ch);

    // 将字符转换为大写
    const char upper_ch = toupper(ch);
    printf("Uppercase of %c is %c.\n", ch, upper_ch);

    return EXIT_FAILURE;
}
