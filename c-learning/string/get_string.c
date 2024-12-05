/*
 * =======================================
 *  获取字符串
 * =======================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * scanf 是 C 标准库中的一个函数，用于从标准输入（通常是键盘）读取格式化的数据。它的原型如下：
 *
 *      int scanf(const char *format, ...);
 *        参数：format 是格式化字符串，类似于 printf 的格式化字符串。
 *        参数：... 表示可变参数列表，这些参数将根据格式化字符串进行解析和存储。
 *
 * 以下是一些常见的格式说明符：
 *
 *  - %d：读取一个十进制整数。
 *  - %f：读取一个浮点数。
 *  - %lf：读取一个双精度浮点数。
 *  - %c：读取一个字符。
 *  - %s：读取一个字符串（直到遇到空白字符）。
*/
static void scanf_sample() {
    // 读取整数
    int numi;
    printf("Enter an integer: ");
    scanf("%d", &numi);
    printf("You entered: %d\n", numi);

    // 读取浮点数
    float numf;
    printf("Enter a float: ");
    scanf("%f", &numf);
    printf("You entered: %f\n", numf);

    // 读取字符串
    char str[100];
    memset(str, 0, sizeof(str));
    printf("Enter a string: ");
    scanf("%s", &numf);
    printf("You entered: %s\n", str);
}

/**
 * 使用 gets() 函数可以获取一个字符串输入，scanf()和转换说明 %s 只能读取一个单词，但是在程序中经常需要读取一整行输入，
 * gets() 函数用于此种情况。
 *
 * gets()函数并不安全，gets()唯一的参数是字符指针，它无法检查数组是否能装下输入行，所以如果如法装下，将导致缓冲区溢出，
 * 如果输入的字符超出指定的空间，字符指针后面未知的内存数据将被重写，造成意想不到的问题。gets()读到文件结尾会返回空指针，
 * C11 标准委员会已经把 gets() 函数从标准中移除。但是很多编译器实现考虑到兼容并没有删除这个函数。
 */
static void gets_sample(void) {
    char str[100];
    // gets(str);
}

/**
 * C11 新增了的 gets_s() 函数和 fgets() 类似，但是更安全。
 *
 * - gets_s() 只从标准输入读取数据。
 * - gets_s() 读到换行符会丢弃它。
 * - 如果读到最大字符数都没有读到换行符，会执行以下处理：把目标数组中的首字符设置为空字符，读取并丢弃随后的输入直至读到换行
 *   符或者文件结尾，然后返回空指针，接着调用依赖实现的处理函数，可能会终止或者退出程序。
 *
 * 注意：gets_s 是 C11 标准引入的函数，但并不是所有的编译器和标准库都完全支持 C11 标准。即使编译器支持 C11 标准，标准库
 * 可能不支持 gets_s 函数。例如，GNU 标准库（glibc）在某些版本中可能不包含 gets_s 函数。
 *
 * 如果你的编译器或标准库不支持 gets_s，可以使用 fgets 函数作为替代。fgets 函数也要求指定缓冲区的大小，并且可以从标准输
 * 入读取字符串。
 */
static void gets_s_sample(void) {
    char buffer[100];

    /*printf("Enter a string: ");
    if (gets_s(buffer, sizeof(buffer)) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return;
    }*/

    printf("You entered: %s\n", buffer);
}

static void fgets_sample(void) {
    char buffer[100];

    printf("Enter a string: ");
    // fgets 函数会读取字符串，直到遇到换行符（\n）、文件结束符（EOF）或读取了 n-1 个字符。如果在读取过程中遇到换行符，
    // fgets 会将换行符包含在字符串中。

    // fgets 返回 NULL 表示读取失败。
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return;
    }

    // 移除换行符（如果存在）
    // strlen：函数返回字符串的长度，不包括空终止符（\0）。
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    printf("You entered: %s\n", buffer);
}

int main() {
    scanf_sample();
    // gets_sample();
    // gets_s_sample();
    // fgets_sample();
    return EXIT_SUCCESS;
}
