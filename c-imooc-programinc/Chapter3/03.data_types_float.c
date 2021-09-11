#include <stdio.h>
#include <limits.h>

int main() {
    //=============== 浮点型 ===============
    /*
     * 怎么理解这个浮：浮点型用科学计数法表示，比如 12345 这个数，可以用 1.2345e4（表示 1.2345 乘以 10 的四次方），浮点类型中会用一部分位来表示基数，另一部分来表示指数。
     * 精确度：精确度随着数值的不同而浮动（即动态调整的）。
     */
    float a_float = 3.14F; // 6, 7~8 +-10^-37 ~ 10^37【现在 C 语言精确度一般在 6-8 位。】
    float b_float = 1.2345e4F;
    printf("size of float: %d\n", sizeof(float));
    printf("a_int: %f\n", b_float);
    double a_double = 3.14; // 15~16
    printf("size of double: %d\n", sizeof(double));

    //=============== 浮点型精确度 ===============
    float lat = 39.90815F;
    //检测精确度：用剪发来验证，第一个不精确的位就是其精确度【可以多数几个数】
    printf("%f\n", 39.90815F - lat);//结果为 0.000000，正确的
    printf("%f\n", 39.90816F - lat);//结果为 0.000011，前五位是正确的，说明精度到 5，到第 6 位就不精确了。
    printf("%f\n", 39.908156f - lat);//这里期望的是 0.000006 结果为 0.000008，说明到第 6 位就不精确了。
    //用双精度后，精确度就更好了
    double d_lat = 39.90815;
    printf("%f\n", 39.908156 - d_lat);//结果为 0.000006，正确的

    //=============== 算钱的功能不能用浮点数 ===============
    float money = 3.14f; // error, never use float or double to describe money
    return 0;
}
