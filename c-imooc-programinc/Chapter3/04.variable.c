#include <stdio.h>
#include <limits.h>

int main() {
    //=============== 变量 ===============
    // <type> <name>;
    int value;
    // <type> <name> = <initialized value>
    int value_init = 3;
    value = 14;
    value_init = 5;
    printf("value: %d\n", value);

    value_init = value;
    //"%#x " 中的 # 用于表示用指定的进制输出，其中 x 的作用是指定输出的禁止，x 就表示输出为 16 进制形式。
    //# indcates an alternative format. For x this means that 0x is prepended to the output.
    // 参考：
    //      <https://stackoverflow.com/questions/3529777/do-you-know-about-x-in-c-language-format-string>
    //      <http://www.cplusplus.com/reference/cstdio/printf/>
    printf("value in hex: %#x\n", value);//16 进制输出
    printf("value in octal: %#o\n", value);//16 进制输出
    printf("size of value: %d\n", sizeof(value));
    printf("address of value: %#x\n", &value);//16 进制输出
    printf("address of value: %#o\n", &value);//8 进制输出

    //=============== 变量命名 ===============
    // key words 标识符 identifier
    // 1. a-zA-Z0-9_
    // 2. 数不能在第一个
    // 3*. Google code style, a-z_a-z，person_name
    float a_float3 = 3.14f;
    float a_float = 3.14f;
    return 0;
}
