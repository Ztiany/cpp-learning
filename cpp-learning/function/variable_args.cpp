/*
 * =======================================
 *  可变参数
 * =======================================
 */

#include <string>
#include <iostream>
#include <initializer_list>

using namespace std;

/**
 * `initializer_list` 是标准中的类型，与 vector 类似， 它是一个模板，`initializer_list` 中的对象永远是常量，
 * `initializer_list` 可用于传递类型相同数量不定的参数。
 */
static void initializerSample() {
    initializer_list<int> lst1;
    const initializer_list<int> lst2{1, 2, 3, 4, 5, 6};
    // 拷贝一个 initializer_list，不会拷贝列表中的元素，拷贝后，原始列表和副本共享元素。
    initializer_list<int> lst3(lst2);
    // 赋值一个 initializer_list，不会拷贝列表中的元素，拷贝后，原始列表和副本共享元素。
    initializer_list<int> lst4 = lst2;

    for (const int i : lst2) {
        cout << i << endl;
    }
}

static void initializerParameter(const initializer_list<string> strings) {
    // 老式 for 循环
    for (auto begin = strings.begin(); begin != strings.end(); begin++) {
        cout << *begin << " ";
    }
    cout << endl;

    // 新的 for 循环：基于范围的 for 循环（Range-based for loop）：这种循环结构允许直接遍历容器中的元素，而无需使用
    // 索引变量。它首次引入于 C++11。
    for (const auto& string : strings) {
        cout << string << " ";
    }
    cout << endl;
}

static void invokeInitializer() {
    initializerParameter({"CBA", "CBA", "CBA"});
    initializerParameter({"NBA", "NBA"});
}


// 基础情况：0 个参数。
static void print1() {
    std::cout << "No arguments" << std::endl;
}

/**
 * 如果实参类型不相同，可以使用可变参数模板。
 *
 *  - T 是一个类型参数，可以是任何类型；
 *  - Args 是一个参数包（parameter pack），它可以包含零个或多个类型参数。参数包是一种特殊的模板参数，用于表示类型列表。
 *
 * 或者 C++17 引入的折叠表达式。
 */
template <typename T, typename... Args>
static void print1(T value, Args... args) {
    std::cout << value << " ";
    // 要遍历一个可变参数模板（Variadic Templates）中的参数包 Args，可以使用递归模板展开。
    print1(args...); // 递归调用，直到基础情况
}

/**
 *  使用 C++17 引入的折叠表达式。
 */
template <typename T, typename... Args>
static void print2(T value, Args... args) {
    // 使用折叠表达式遍历参数包
    ((std::cout << args << " "), ...);
    // 打印换行符
    std::cout << std::endl;
}

// 基础情况：0 个参数。
static void print3() {
    std::cout << "No arguments" << std::endl;
}

/**
 *  如果你需要对可变参数模板 args 中的每个类型进行判断，C++17 引入的折叠表达式可能不是最适合的工具，因为它主要用于执行统
 *  一的操作，而不是进行条件判断或类型检查。在这种情况下，你可以使用递归模板展开或者 C++17 中的 if constexpr 来实现类
 *  型判断和相应的操作。
 */
template <typename T, typename... Args>
static void print3(T first, Args... args) {
    // 对第一个参数进行类型判断和处理。
    if constexpr (std::is_integral_v<T>) {
        std::cout << "Integral: " << first << std::endl;
    } else if constexpr (std::is_floating_point_v<T>) {
        std::cout << "Floating point: " << first << std::endl;
    } else {
        std::cout << "Other type: " << first << std::endl;
    }
    // 递归调用，处理剩余参数。
    print3(args...);
}

class MyClass {

};

/**
 * 为了编写能处理不同数量实参的参数，C++11 提供了两种方法：
 *
 *  - 如果实参的类型相同，可以传递 initializer_list 的标准类型库。
 *  - 如果实参类型不相同，可以使用可变参数模板。
 */
int main() {
    invokeInitializer();
    print1(1, 2, 3.5, "Hello", 'A');
    print2(1, 2, 3.5, "Hello", 'A');
    print3(1, 2, 3.5, "Hello", 'A');
    return 0;
}
