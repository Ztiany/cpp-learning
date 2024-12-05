#ifndef C_BASIC_COPY_H
#define C_BASIC_COPY_H

#include <iostream>

class Line {
public:
    [[nodiscard]] int getLength() const;

    explicit Line(int len);

    Line(const Line& obj);

    Line& operator=(const Line& obj);

    ~Line();

private:
    int* ptr;
};

// 成员函数定义，包括构造函数
inline Line::Line(const int len) {
    std::cout << "construct" << std::endl;
    // 为指针分配内存
    ptr = new int;
    *ptr = len;
}

inline Line::Line(const Line& obj) {
    std::cout << "copy constructor" << std::endl;
    ptr = new int;
    *ptr = *obj.ptr; // 拷贝值
}

inline Line::~Line() {
    std::cout << "release dynamic_memory" << std::endl;
    delete ptr;
}

inline int Line::getLength() const {
    return *ptr;
}

inline Line& Line::operator=(const Line& obj) {
    if (this == &obj) {
        std::cout << "self-assignment" << std::endl;
        return *this;
    }
    std::cout << "copy assignment" << std::endl;
    delete ptr;
    ptr = new int;
    *ptr = *obj.ptr;
    return *this;
}

#endif