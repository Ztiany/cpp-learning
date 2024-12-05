/*
 * =======================================
 *  数组
 * =======================================
 */

#include <iostream>
#include <vector>

using namespace std;

// 1：初始化数组
static void initializeArray() {
    int size = 3;
    constexpr int cSize = 10;
    int arr1[size];
    int arr2[] = {1, 2, 3};
    int arr3[5] = {1, 2, 3};
    string arr4[7] = {"a", "bc", "dd"};
    int arr5[cSize];

    const char* arr6 = "abc";
    char arr7[10] = "C++";
    char arr8[] = {'c', '+', '+', '\0'};

    int* p1[10]; //pInt 是指向含有是个整型元素的数组的指针
    int arr9[10][10];
    int (*arr10)[10] = arr9; //arr10 是一个指针数组
    int (&arrRef)[5] = arr3; //arrRef 引用一个含有 5 个元素的 int 数组

    cout << "arr5[1] = " << arr5[5] << endl;
}

// 2：访问数组
static void accessArray() {
    // 通过下标访问数组时，通常将其定义为 size_t
    int arr[10];
    for (int i = 0; i < 10; ++i) {
        arr[i] = i;
    }
    constexpr size_t index = 4;
    int i4 = arr[index];
}

// 3：数组与指针、迭代器
static void arrayPointer() {
    int arr[]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int* pInt1 = arr;
    int* pInt2 = begin(arr); // 等同于 pInt1
    int* end_1 = &arr[10]; // 指向尾元素
    int* end_2 = end(arr); // 等同于 end_1

    // 遍历 arr
    for (int* p = pInt1; p != end_1; ++p) {
        cout << (*p);
    }
    cout << endl;

    // 指针相减的结果是 ptrdiff_t 类型，它是一个带符号的整型
    const ptrdiff_t pt = end_1 - pInt1;
    cout << pt << endl; //10

    //下标和指针
    const int arr2[] = {1, 2, 3, 4, 5};
    const int* pInt3 = arr2;
    int int_1 = *(++pInt3);
    int int_2 = pInt3[-2];
}

// 4：使用数组初始化 vector
static void arrayInitializeVector() {
    //允许使用数组来初始化vector对象
    int arr[]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    //用于创建 vec 的两个指针指定了用来初始化的值在数组中的位置
    //  第一个指针，起始拷贝地址
    //  第二个指针，待拷贝区域尾元素的下一个位置
    const vector vec1(begin(arr), end(arr));
    const vector vec2(arr + 1, arr + 4); // 拷贝三个元素
    cout << "vec1 size = " << vec1.size() << endl;
    cout << "vec2 size = " << vec2.size() << endl;
}

int main() {
    initializeArray();
    accessArray();
    arrayPointer();
    arrayInitializeVector();
    return EXIT_SUCCESS;
}
