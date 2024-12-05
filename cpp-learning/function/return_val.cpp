/*
 * =======================================
 *  函数返回类型
 * =======================================
 */

#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

// 1：返回值，拷贝值。
static string shortString(const string& s1, const string& s2) {
    return s1.size() > s2.size() ? s2 : s1;
}

// 2：返回引用，不拷贝值。
const static string& shortString(const string s1, const string s2) {
    // 严重错误：返回局部变量的引用。
    // The address of the parameter 's2' may escape the function.
    return s1.size() > s2.size() ? s2 : s1;
}

// 3：返回列表。
static vector<string> getMessage() {
    // 列表转换为 vector。
    return {"A", "B", "C"};
}

// 4：严重错误：返回局部变量的引用。
static string& getString() {
    string ret;
    if (ret.empty()) {
        ret = "empty";
    }
    // 当函数执行完毕时，将释放分配给局部对象的存储空间。此时，对局部对象的引用就会指向不确定的内存。
    // The address of the parameter 'ret' may escape the function.
    return ret;
}

// 5：返回数组指针
typedef int arrI[10];
// 或者使用 using，这等价于上面声明
using arrI = int[10];

// 如果没有用到函数声明，该函数可以没有定义。
static arrI* getIntegers();

static arrI* getIntegers() {
    int (*pInt)[10] = new int[1][10];
    return pInt;
}

static int (* returnArray(int i))[10] {
    int (*pInt)[10] = new int[1][10];
    return pInt;
}

// 5：返回数组指针
void returningArrPointer() {
    const int (*pInt)[10] = getIntegers();
    delete[]pInt;
}

// 6：C++ 11 规定，函数可以返回花括号包围的值的列表。返回的列表用于对函数返回的临时量做初始化：
static vector<int> returnBracket() {
    return {1, 2, 3, 4};
}

/**
 * 返回值三个注意点：
 *
 * - 一般情况下，返回值将被拷贝到调用点。
 * - 如果函数返回的是引用类型，则不会存在拷贝。
 * - 不要返回局部对象的指针或引用。
 *
 * 要确保返回值的安全，可以问自己：引用所引的是在函数之前已经存在的那个对象吗？
 */
int main() {
    returningArrPointer();
    return EXIT_SUCCESS;
}
