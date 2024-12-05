#ifndef C_BASIC_LINE_H
#define C_BASIC_LINE_H

#include <iostream>

class Line {
public:
    // 成员函数
    void setLength(double len);

    /**
     * [[nodiscard]] 是 C++17 标准中引入的一个属性属性（attribute），用于标记函数，提示调用者不应该忽略该函数的返回
     * 值。如果调用者没有使用带有 [[nodiscard]] 属性的函数的返回值，编译器会发出警告。
     */
    [[nodiscard]] double getLength() const;

    void setWidth(double len);
    [[nodiscard]] double getWidth() const;

    // 构造函数
    Line() {
        std::cout << "use default length = 1, width = 1" << std::endl;
        this->length = 1;
        this->width = 1;
    }

    explicit Line(double len);

    Line(double len, double width);

    // 析构函数
    ~Line() {
        std::cout << "Object line is being deleted" << std::endl;
    }

private:
    // 线的长度
    double length;
    // 线的宽度
    double width;
};

// 成员函数定义，包括构造函数
inline Line::Line(const double len) {
    std::cout << "Object is being created, length = " << len << std::endl;
    length = len;
    width = 1;
}

// 使用初始化列表来初始化字段
inline Line::Line(const double len, const double width) : length(len), width(width) {
    std::cout << "Object is being created, length = " << len << "width = " << width << std::endl;
}

inline void Line::setLength(const double len) {
    length = len;
}

inline double Line::getLength() const {
    return length;
}

inline void Line::setWidth(const double len) {
    length = len;
}

inline double Line::getWidth() const {
    return width;
}

#endif
