/*
 * =======================================
 *  delctype
 * =======================================
 */

#include <cstdlib>

int decltype_type() {
    const int ci = 0, &cj = ci;
    decltype(ci) x = 0; //x 的类型是 const int
    decltype(cj) y = x; //y 的类型是 const int&，y 绑定到了 x
    //decltype(cj) z; // decltype(cj) 是引用类型，必需初始化

    int i = 4, h = 44, *p = &i, &r = i;
    decltype(r + 0) b; // 加法的结果是一个 int，所以 b 的类型是一个 int 类型
    /*
     * (*p) 是引用类型 int&，必需被初始化。如果表达式的内容是解引用操作，则 decltype 将得到引用类型。
     * 正如我们熟悉的那样，解引用指针可以得到指针所指的对象，而且还能给这个对象赋值，因此 decltype(*p) 的结果就是 int&，
     * 而非 int。
     */
    decltype(*p) c = i;
    decltype(i) j;

    // decltype((i)) 形式的结果永远是引用，而 decltype(i) 只有当 i 本身是一个引用的时候才是引用。
    decltype((i)) rB = h;

    return EXIT_SUCCESS;
}
