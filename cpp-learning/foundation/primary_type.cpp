/*
 * =======================================
 *  基础数据类型
 * =======================================
 */

// 输入输出
#include <iostream>
// 包含各种整型类型的系统限制
#include <climits>
// 包含各种浮点类型的系统限制
#include <cfloat>
// C 标准库
#include <cstdlib>

void integer_type() {
    /*-----------------short 类型-----------------*/
    short sa = 22;
    unsigned short usa = 32u; // u 作为后缀表示无符号，用于指定字面值类型。


    /*-----------------int 类型-----------------*/
    int a; // a 是不确定的
    int b(2);
    int c{3};
    int d = {4};
    int e{}; // e = 0，C++11 的列表初始化
    unsigned int f;
    unsigned quarterback; // 不指定类型，默认是 int
    int g = 02; //八进制
    int h = 0xF; //十六进制
    // 堆中申请int
    int* newInt = new int;
    delete (newInt);


    /*-----------------long 类型-----------------*/
    long la = 32;
    long long lla = 332;
    unsigned long long ulla = 32ULL; //ULL是后缀
}

void char_type() {
    /*-----------------char 类型-----------------*/
    // char 在默认的情况下既不是有符号的，也不是无符号的，是否有符号由 C++ 实现决定。
    // char 类型的大小被定义为一个字节（byte），即 C++ 标准保证 sizeof(char) 始终为 1。这意味着一个 char 的大小和一
    // 个机器字节的大小是一样的。
    char i = 'a';
    int j = i;

    // 字符：wchar_t 是一种整数类型，它有足够的空间，可以表示系统的最大扩展字符集
    // wchar_t底层的类型取决于编译器实现，在一种系统中可能是 unsigned short，在另一种系统中又可能是 int。
    // cin 和 cout 将输入和输出看作是字符流，因此不适合用来处理 whcar_t 类型。
    wchar_t w_char = L'我';
    wchar_t l_w_char = L'p'; // 使用 L 来指示宽字符常量和宽字符串

    // 设置全局“区域设置”为支持宽字符输出
    std::locale::global(std::locale(""));// 创建一个与系统默认区域设置相对应的 std::locale 对象。
    std::wcout.imbue(std::locale());// 将这个 std::locale 对象设置为全局区域设置。
    // 才能正确打印中文宽字符
    wprintf(L"Characters: %lc %lc \n", L'a', w_char);
    std::wcout << L"The character is: " << l_w_char << std::endl;

    // C11：char16_t 和 char32_t 是内置类型，用于处理 unicode 字符，它们都是无符号的，但是底层类型可能跟随系统
    char16_t char_16 = u'q';
    char32_t char_32 = U'我';
}

void bool_type() {
    /*-----------------布尔类型-----------------*/
    bool is_real = true;
    bool stop = 1;
    bool start = 0;
}

void float_type() {
    /*-----------------浮点类型-----------------*/
    // 浮点常量默认为 double
    float l = 32.3;
    double n = 32.323;
    float m = 32.333F;
    long double ldm = 323.32L;
    float max = FLT_MAX;
}

void type_conversation() {
    /*-----------------类型转换-----------------*/
    int o = (int)(33.3); // 转换为 33
    int p = (int)32.3;
    // int q = {32.3}; // 大括号"{}"的方式很严格，不允许这种操作【不会自动转换】
    int q = {33}; // 这种才行

    /*-----------------定义常量-----------------*/
    //定义常量，应该使用 const 来定义常量，而不是 #defind
    const int k = 32;
}

void sizeof_and_limitation() {
    /*-----------------数据类型的大小-----------------*/
    std::cout << "sizeof(int) = " << sizeof(int) << std::endl;
    std::cout << "INT_MIN = " << INT_MIN << std::endl;
    std::cout << "INT_MAX = " << INT_MAX << std::endl;
    std::cout << "CHAR_BIT = " << CHAR_BIT << std::endl;
    std::cout << "LONG_MAX = " << LONG_MAX << std::endl;
    std::cout << "LONG_MAX = " << FLT_MAX << std::endl;
}

void unsigned_type() {
    /*-----------------无符号类型计算-----------------*/
    // 不要混用有符号类型的数据和无符号类型的数据
    int va = -1;
    unsigned int vb = 1;
    int vc = va * vb; //此时 va 会自动转为为无符号类型的整数
}

int main() {
    integer_type();
    char_type();
    bool_type();
    float_type();
    type_conversation();
    sizeof_and_limitation();
    unsigned_type();
    return EXIT_SUCCESS;
}