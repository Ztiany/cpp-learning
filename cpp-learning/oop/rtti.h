#ifndef CPLUSPLUS_PROGRAM_RTTI_H
#define CPLUSPLUS_PROGRAM_RTTI_H

#include <string>
#include <iostream>

class BaseWithVirtual {
private:
    std::string name;
    int age;

public:
    BaseWithVirtual(const std::string& _name, const int _age) : name(_name), age(_age) {}

    virtual ~BaseWithVirtual() = default;

    virtual void printInfo() {
        std::cout << "name = " << name << ", age = " << age << std::endl;
    }

    /*
     * [[nodiscard]] 是 C++17 中引入的一个属性属性（attribute），它用于告诉编译器，函数返回的值不应该被忽略。当你在
     * 函数的返回类型前添加[[nodiscard]]时，如果调用该函数的代码没有使用函数的返回值，编译器会发出警告。
     *
     * 这个属性的目的是防止开发者无意中忽略重要的函数返回值，这在一些特定情况下非常有用。例如，某些函数可能返回错误代码或者
     * 状态信息，如果这些返回值被忽略，可能会导致程序的行为不如预期。
     */
    [[nodiscard]] std::string getName() const {
        return name;
    }

    [[nodiscard]] int getAge() const {
        return age;
    }
};


class DeriveWithVirtual final : public BaseWithVirtual {
private:
    std::string address;

public:
    DeriveWithVirtual(
        const std::string& _name,
        const int _age,
        const std::string& _address
    ): BaseWithVirtual(_name, _age), address(_address) {}

    void printInfo() override {
        std::cout << "name = " << getName() << ", age = "
            << getAge() << ", address = " << address << std::endl;
    }
};


class BaseWithoutVirtual {
private:
    std::string name;
    int age;

public:
    BaseWithoutVirtual(const std::string& _name, const int _age) : name(_name), age(_age) {}

    void printInfo() const {
        std::cout << "name = " << name << ", age = " << age << std::endl;
    }

    [[nodiscard]] std::string getName() const {
        return name;
    }

    [[nodiscard]] int getAge() const {
        return age;
    }
};

class DeriveWithoutVirtual : public BaseWithoutVirtual {
private:
    std::string address;

public:
    DeriveWithoutVirtual(
        const std::string& _name,
        const int _age,
        const std::string& _address
    ): BaseWithoutVirtual(_name, _age), address(_address) {}

    void printInfo() const {
        std::cout << "name = " << getName() << ", age = "
            << getAge() << ", address = " << address << std::endl;
    }
};

#endif