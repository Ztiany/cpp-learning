/*
 * =======================================
 * 显式类型转换
 * =======================================
 */

#include <iostream>

using namespace std;

class Building {};

class Animal {};

class Cat : public Animal {};

/**
 * static_cast 用于内置的数据类型、具有继承关系的指针或者引用。
 */
static void test01() {
    // 基础类型转换
    int a = 97;
    char c = static_cast<char>(a);
    cout << c << endl;


    // 基础数据类型指针
    int* p = nullptr;
    // Cannot cast from int* to char* via static_cast.
    // char* sp = static_cast<char*>(p);


    // 对象指针
    Building* building = nullptr;
    // Cannot cast from Building* to Animal* via static_cast.
    // Animal* ani = static_cast<Animal*>(building);


    // 转换具有继承关系的对象指针
    // 父类指针转成子类指针
    Animal* ani = nullptr;
    Cat* cat1 = static_cast<Cat*>(ani);
    // 子类指针转成父类指针
    Cat* cat2 = nullptr;
    Animal* anifather = static_cast<Animal*>(cat2);
    // 父类引用转成子类引用
    Animal animal1;
    Animal& animal_ref1 = animal1;
    Cat& cat = static_cast<Cat&>(animal_ref1);
    // 子类引用转成父类引用
    Cat cat3;
    Cat& cat_ref3 = cat3;
    Animal& animal_ref3 = static_cast<Animal&>(cat_ref3);
}

/**
 * dynamic_cast 只能转换具有继承关系的指针或者引用，并且只能由子类型转成基类型。
 */
void test02() {
    // 基础数据类型
    int a = 10;
    // Cannot cast from int to char via dynamic_cast: conversion to non-class type is not allowed.
    // char c = dynamic_cast<char>(a);

    // 非继承关系的指针
    Animal* ani1 = nullptr;
    // Cannot cast from Animal* to Building* via dynamic_cast: expression type is not polymorphic.
    // Building* building = dynamic_cast<Building*>(ani);

    // 具有继承关系指针
    Animal* ani2 = nullptr;
    // Cannot cast from Animal* to Cat* via dynamic_cast: expression type is not polymorphic.
    // 原因在于 dynamic 做类型安全检查
    // Cat* cat = dynamic_cast<Cat*>(ani2);

    // 可以
    Cat* cat = nullptr;
    Animal* ani = dynamic_cast<Animal*>(cat);
}

/**
 * const_cast 用于指针、引用或者对象指针。作用是增加或者去除变量的 const 性质。
 */
void test03() {
    const int a = 10;
    const int& pp = a;
    int& cc = const_cast<int&>(pp);
    cc = 100;
    cout << "a:" << a << endl;

    const int* p = nullptr;
    int* p2 = const_cast<int*>(p);

    int* p3 = nullptr;
    const int* p4 = const_cast<const int*>(p3);
}

typedef void (*FUNC1)(int, int);
typedef int (*FUNC2)(int, char*);

/**
 * reinterpret_cast 强制类型转换 无关的指针类型，包括函数指针都可以进行转换。
 */
void test04() {
    // 1. 无关的指针类型都可以进行转换。
    Building* building = nullptr;
    Animal* ani = reinterpret_cast<Animal*>(building);

    // 2. 函数指针转换
    FUNC1 func1;
    FUNC2 func2 = reinterpret_cast<FUNC2>(func1);
}

int main() {
    test01();
    test03();
    return 0;
}
