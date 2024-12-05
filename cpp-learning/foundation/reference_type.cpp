/*
 * =======================================
 *  引用
 * =======================================
 */

#include "cstdlib"
#include "iostream"

using namespace std;

// 1：引用类型
static void reference() {
    int value_a = 323;
    int& ref_a = value_a; //ref_a 指向 value_a
    //int &ref_b; //报错，引用类型必需被初始化
    ref_a = 3;
    cout << "value_a = " << value_a << endl;
}

// 2：指针类型
static void pointer() {
    int value_a = 32;
    int* pA = &value_a;
    void* pVoid = &value_a;
    int*& refPa = pA; //refPa 是对指针 pA 的引用
    cout << "value_a address = " << pA << endl;

    const int* pB = &value_a; //pB 是一个指向整型常量的指针，pB 不能修改其地址所指向的值
    int* const pC = &value_a; //pC 是一个指针常量，pC 不能再指向其他 int 变量
}

// 3：const与引用
static void cons_reference() {
    int value_a = 3;
    const int& ref_a1 = value_a;
    const int& ref_a2 = 3;
    const int& ref_a3 = ref_a1 * 3;

    const int value_b = 3;
    //int &ref_b = value_b; //编译错误，因为 value_b 是一个常量，所以必需使用引用也必须是一个常量
}

/**
 * 引用（reference）是一个别名，它提供了对另一个变量的直接访问。引用本身并不占用额外的内存空间来存储引用对象的值，而是直
 * 接引用已经存在的变量。
 *
 * 引用本身并不占用额外的内存空间来存储引用对象的值。引用的实现通常是通过编译器的优化来实现的，编译器会在编译时将引用替换为
 * 被引用的变量。因此，引用并不会增加额外的内存开销。
 */
int main() {
    reference();
    pointer();
    return EXIT_SUCCESS;
}
