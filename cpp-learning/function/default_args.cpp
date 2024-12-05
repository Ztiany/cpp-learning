/*
 * =======================================
 *  默认参数
 * =======================================
 */

#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

typedef string::size_type sz;

/**
 * 参数中可以定义默认参数。
 */
static string screen(sz ht = 24, sz wid = 80, char back = ' ');

/**
 * 当定义一个函数时，可以为参数列表中后边的每一个参数指定默认值。当调用函数时，如果实际参数的值留空，则使用这个默认值。这是
 * 通过在函数定义中使用赋值运算符来为参数赋值的。调用函数时，如果未传递参数的值，则会使用默认值，如果指定了值，则会忽略默认
 * 值，使用传递的值。
 *
 * 局部变量不能作为参数的默认参数，除此之外，只要表达式的类型能够转换成形参所需的类型，该表达式就能作为默认实参。既可以在函
 * 数声明也可以在函数定义中指定默认实参。但是在一个文件中，只能为一个形参指定默认实参一次。
 */
int main() {
    string window{};

    window = screen();
    window = screen(33);
    window = screen(33, 44);
    window = screen(33, 44, '#');

    sz local = 55;
    // 局部变量不能作为默认实参
    //window(locale)

    return EXIT_SUCCESS;
}

static string screen(const sz ht, const sz wid, const char back) {
    cout << "----------------------------------------------" << endl;
    cout << "ht = " << ht << endl;
    cout << "wid = " << wid << endl;
    cout << "back = " << back << endl;
    return "Fake Screen";
}
