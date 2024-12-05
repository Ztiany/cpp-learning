/*
 * =======================================
 *  函数声明
 * =======================================
 */

#include <iostream>
#include <array>
#include <vector>

using namespace std;

/**
 * 引用形参，通过传递引用形参，可以改变实参的值。
 */
static void referenceParameter1(int& i) {
    // 我们改变了 i 的值，利用这个特性，可以把参数用作返回额外从信息的载体。
    i = 4;
}

/**
 * 把参数声明为引用类型，可以避免是实参被拷贝，这里只会传递实参的引用。
 */
static bool referenceParameter2(const string& s1, const string& s2) {
    return s1.size() > s2.size();
}

/**
 * const 形参：如果参数不需要被修改，应该声明为 const 的。
 */
static void constParameter1(const char* cp) {
    if (cp) {
        while (*cp) {
            cout << *cp << ", ";
            cp++;
        }
    }
    cout << endl;
}

/**
 * 使用普通引用而非常量引用极大的限制了函数能接受的实参类型，这个函数只能接受非常量类型。
 */
static void constParameter2(char* cp) {
    if (cp) {
        while (*cp) {
            cout << *cp << ", ";
            cp++;
        }
    }
    cout << endl;
}

/**
 * 数组传参，这里的 arr[10] 只表示期望给一个长度为 10 的数据，但实际长度却不确定。
 */
static void arrayParameter1(int arr[10]) {
    cout << "array_parameter " << arr << endl;
}

/**
 * 标准做法，传入头和尾，遍历数组。
 */
static void arrayParameter2(const int* begin, const int* end) {
    while (begin != end) {
        begin++;
    }
}

/**
 * 从避免复制 vector 的角度出发，应考虑将形参声明为引用类型。然而事实上，C++ 程序员倾向于通过传递指向容器中需要处理的元素
 * 的迭代器来传递容器。
 */
static void vectorParameter(vector<int>::const_iterator beg, const vector<int>::const_iterator end) {
    while (beg != end) {
        cout << *beg++;
        if (beg != end) cout << " "; // no space after last element
    }
    cout << endl;
}

/**
 * 标准做法，传入数组和数组的长度。
 */
static void arrayParameter3(const int* arr, const size_t size) {}

int main(const int argc, char* argv[]) {
    // 1：获取 main 函数的参数。
    cout << argc << endl;
    for (int i = 0; i < argc; ++i) {
        cout << argv[i] << endl;
    }


    // 2：引用作为形参。
    int intA = 1;
    referenceParameter1(intA);
    cout << "intA =" << intA << endl;


    // 3：常量形参。
    char* str1 = "abcdefg";
    const char* str2 = "hijklmn";
    constParameter1(str1);
    constParameter1(str2);
    constParameter2(str1);
    // 常量类型传递给非产量类型时，类型不匹配：
    // Parameter type mismatch: Assigning 'const char *' to 'char *' discards const qualifier
    //constParameter2(str2);


    // 4：形成为数组。
    int array[]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    arrayParameter1(array);
    arrayParameter2(begin(array), end(array));
    // std::size(array) = sizeof(array) / sizeof(array[0])
    arrayParameter3(array, std::size(array));
}
