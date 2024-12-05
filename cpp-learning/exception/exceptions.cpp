/*
 * =======================================
 * 异常处理
 * =======================================
 */

#include <iostream>

using namespace std;

static void tryCatch() {
    try {
        // throw 用于抛出异常
        throw exception();
    } catch (exception& e) {
        cout << e.what() << endl;
    }

    try {
        throw logic_error("throw error");
    } catch (logic_error& logicError) {
        cout << logicError.what() << endl;
    }
}


struct MyException final : exception {
    [[nodiscard]] const char* what() const noexcept override {
        return "C++ Exception";
    }
};


void customException() {
    try {
        throw MyException();
    } catch (MyException& e) {
        std::cout << "MyException caught" << std::endl;
        std::cout << e.what() << std::endl;
    }
    catch (std::exception& e) {
        //其他的错误
    }
}


/*
 * 异常接口声明：在 C++ 中，函数可以声明它抛出的异常类型，这被称为异常规范。这个规范允许编译器在函数抛出不符合声明的异常类
 *            型时生成一个编译错误。下面这个函数只能抛出 int float char 三种类型异常，抛出其他的程序就报错。
 *
 * C++17 开始禁用：ISO C++17 does not allow dynamic exception specifications.
 *
 * 警告信息：Dynamic exception specification 'throw(int, float, char)' is deprecated;
 *         consider using 'noexcept(false)' instead.
 *
 * noexcept(false)：这是建议的替代方案。noexcept 关键字用于声明一个函数不会抛出任何异常，或者如果抛出了异常，那么程序将
 * 调用 std::terminate() 来终止程序。而 noexcept(false) 表示函数可能会抛出异常，并且不会对抛出的异常类型做任何限制。
 */
/*static void func() throw(int, float, char) {
    throw "abc";
}*/


/**
 * 不能抛出任何异常。
 */
void func02() noexcept {
    // Clang-Tidy: Throwing an exception whose type 'int' is not derived from 'std::exception'.
    throw -1;
}

/**
 * 该函数可以抛出任何类型异常。
 */
void func03() {}

void exceptionInterface() {
    try {
        func03();
    } catch (char* str) {
        cout << str << endl;
    }
    catch (int e) {
        cout << "异常!" << endl;
    }
    catch (...) {
        // 捕获所有异常
        cout << "未知类型异常！" << endl;
    }
}

int main() {
    tryCatch();
    customException();
    exceptionInterface();
    return EXIT_SUCCESS;
}
