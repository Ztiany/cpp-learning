#ifndef CPLUSPLUS_PROGRAM_MOVE_CONSTRUCTOR_H
#define CPLUSPLUS_PROGRAM_MOVE_CONSTRUCTOR_H

#include <string>
#include <iostream>

class MoveClass {
    std::string* name;

public:
    MoveClass() : name(nullptr) {
        std::cout << "MoveClass()" << std::endl;
    }

    explicit MoveClass(const std::string& name) : name(new std::string(name)) {
        std::cout << name << " MoveClass()" << std::endl;
    }

    MoveClass(const MoveClass& other) {
        if (other.name) {
            name = new std::string(*other.name);
        } else {
            name = nullptr;
        }
        if (name) {
            std::cout << *name << " copy MoveClass()" << std::endl;
        } else {
            std::cout << "copy MoveClass()" << std::endl;
        }
    }

    MoveClass& operator=(const MoveClass& other) {
        if (this == &other) {
            return *this;
        }
        delete name;
        if (other.name) {
            name = new std::string(*other.name);
        }
        if (name) {
            std::cout << *name << " operator= MoveClass()" << std::endl;
        } else {
            std::cout << "operator= MoveClass()" << std::endl;
        }
        return *this;
    }

    MoveClass(MoveClass&& other) noexcept: name(other.name) {
        // 将源对象置为可析构状态
        other.name = nullptr;
        if (name) {
            std::cout << *name << " move MoveClass()" << std::endl;
        } else {
            std::cout << "move MoveClass()" << std::endl;
        }
    }

    MoveClass& operator=(MoveClass&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        // 使用已有的资源
        delete name;
        // 执行资源拷贝
        if (other.name) {
            name = other.name;
        }
        // 将源对象置为可析构状态
        other.name = nullptr;
        if (name) {
            std::cout << *name << " operator= move MoveClass()" << std::endl;
        } else {
            std::cout << "operator= move MoveClass()" << std::endl;
        }
        return *this;
    }

    ~MoveClass() {
        if (name) {
            std::cout << *name << "  ~" << "MoveClass()" << std::endl;
        } else {
            std::cout << "~" << "MoveClass()" << std::endl;
        }
        delete name;
    }
};

class NoMoveClass {
    std::string* name;

public:
    NoMoveClass() : name(nullptr) {
        std::cout << "NoMoveClass()" << std::endl;
    }

    explicit NoMoveClass(const std::string& name) : name(new std::string(name)) {
        std::cout << name << " NoMoveClass()" << std::endl;
    }

    NoMoveClass(const NoMoveClass& other) {
        if (other.name) {
            name = new std::string(*other.name);
        } else {
            name = nullptr;
        }

        if (name) {
            std::cout << *name << " copy NoMoveClass()" << std::endl;
        } else {
            std::cout << "copy NoMoveClass()" << std::endl;
        }
    }

    NoMoveClass& operator=(const NoMoveClass& other) {
        if (this == &other) {
            return *this;
        }
        delete name;
        if (other.name) {
            name = new std::string(*other.name);
        }
        if (name) {
            std::cout << *name << " operator= NoMoveClass()" << std::endl;
        } else {
            std::cout << "operator= NoMoveClass()" << std::endl;
        }
        return *this;
    }

    ~NoMoveClass() {
        if (name) {
            std::cout << *name << "  ~" << "NoMoveClass()" << std::endl;
        } else {
            std::cout << "~" << "NoMoveClass()" << std::endl;
        }
        delete name;
    }
};

#endif
