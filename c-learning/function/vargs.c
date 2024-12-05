/*
 * =======================================
 *  可变参数
 * =======================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

static void traditional(int a, ...) {
    printf("a: %d, $a: %p \n", a, &a);
    int* temp = &a;
    temp++;
    for (int i = 0; i < a; ++i) {
        printf("%d %d \n", *temp, temp);
        temp++;
    }
}

/**
 * ANSI 标准形式的声明方式，括号内的省略号表示可选参数。获取可变参数：
 *
 *  1. typedef char* va_list;
 *  2. void va_start ( va_list ap, prev_param );
 *  3. type va_arg ( va_list ap, type );
 *  4. void va_end ( va_list ap );
 *
 * va_list 是一个字符指针，可以理解为指向当前参数的一个指针，取参必须通过这个指针进行。
 *
 * - step 1：在调用参数表之前，定义一个 va_list 类型的变量，(假设 va_list 类型变量被定义为 ap)；
 * - step 2：然后应该对 ap 进行初始化，让它指向可变参数表里面的第一个参数，这是通过 va_start 来实现的，第一个参数是 ap
 *           本身，第二个参数是在变参表前面紧挨着的一个变量,即“...”之前的那个参数；
 * - step 3：然后是获取参数，调用 va_arg，它的第一个参数是 ap，第二个参数是要获取的参数的指定类型，然后返回这个指定类型
 *           的值，并且把 ap 的位置指向变参表的下一个变量位置；
 * - step 4：获取所有的参数之后，我们有必要将这个 ap 指针关掉，以免发生危险，方法是调用 va_end，他是输入的参数 ap 置为
 *           NULL，应该养成获取完参数表之后关闭指针的习惯。说白了，就是让我们的程序具有健壮性。通常 va_start 和 va_end
 *           是成对的。
 */
static int vargs_function(char* msg, ...) {
    va_list argp;
    int argno = 0;
    char* para;

    va_start(argp, msg);
    while (1) {
        para = va_arg(argp, char*);
        if (strcmp(para, "") == 0)
            break;
        printf("parameter #%d is : %s\n", argno, para);
        argno++;
    }
    va_end(argp);
    return 0;
}

int main() {
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    traditional(4, a, b, c, d);

    vargs_function("DEMO", "This", "is", "a", "demo!", "");
    return EXIT_SUCCESS;
}
