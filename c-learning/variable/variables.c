/*
 * =======================================
 *  C 语言的数据类型
 * =======================================
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// 宏定义
#define A 1.3

// const 定义常量更灵活，可以定义数组。
const int days[3] = {1, 2, 3};

// 如果函数写在 main 后面，需要在 main 函数前面先声明这个函数。
static void all_variables();

static void variable_address();

// C 程序一定是从主函数开始执行的，main 函数的返回值为 int 类型。
int main() {
    // 数据类型与数据类下大小
    all_variables();

    // 获取内存地址
    variable_address();
    return EXIT_SUCCESS;
}

/**
 * 所谓类型，就是对数据分配存储单元的安排，包括存储单元的长度（占多少字节）
 * 以及数据的存储形式，不同的类型分配不同的长度和存储形式。
 */
static void all_variables() {
    // C 语言中的数据类型
    char c = 'c';
    short s = 1233;
    int d = 12312312;
    long ld = 432432;
    long long lld = 232423423;
    unsigned int ud = 323;
    unsigned long uld = 3333;
    float f = 1212.132121F;
    double lf = 232.222222222;
    // 布尔类型，C99 添加
    bool flag = false;
    _Bool b1 = 1;
    _Bool b2 = 0;

    // 打印变量
    printf("char:\t %c\n", c);
    printf("short:\t %hd\n", s);
    printf("int:\t %d\n", d);
    printf("long:\t %ld\n", ld);
    printf("long_long:\t %lld\n", lld);
    printf("unsigned_int:\t %d\n", ud);
    printf("unsigned_long:\t %ld\n", uld);
    printf("float:\t %f\n", f);
    printf("double:\t %lf\n", lf);
    printf("bool:\t %d\n", flag);
    printf("_Bool:\t %d\n", b1);
    printf("_Bool:\t %d\n", b2);
    printf("#define:\t %f\n", A);

    // 打印数据类型的长度
    printf("字符的长度是：\t%zd\n", sizeof(char));
    printf("short 的长度是：\t%zd\n", sizeof(short));
    printf("int 的长度是：\t%zd\n", sizeof(int));
    printf("long 的长度是：\t%zd\n", sizeof(long));
    printf("long long 的长度是：\t%zd\n", sizeof(long long));
    printf("float 的长度是：\t%zd\n", sizeof(float));
    printf("double 的长度是：\t%zd\n", sizeof(double));
}

//获取与打印内存地址
static void variable_address() {
    int i1 = 3;
    int i2 = 3;
    printf("address of i1: %p\n", &i1);
    printf("address of i2: %p\n", &i2);
}
