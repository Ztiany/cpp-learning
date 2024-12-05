/*
 * =======================================
 * rtti
 * =======================================
 */

#include "rtti.h"
#include <string>
#include <cstdlib>

using namespace std;

static void dynamicCastTest1(DeriveWithVirtual* deriveWithVirtual) {
    BaseWithVirtual* baseWithVirtualTempP = deriveWithVirtual;
    if (auto* tempP = dynamic_cast<DeriveWithVirtual*>(baseWithVirtualTempP)) {
        cout << "dynamic_cast<DeriveWithVirtual *>(&baseWithVirtual) success" << endl;
        tempP->printInfo();
    } else {
        cout << "dynamic_cast<DeriveWithVirtual *>(&baseWithVirtual) failed" << endl;
    }
}

static void dynamicCastTest2(DeriveWithVirtual& deriveWithVirtual) {
    BaseWithVirtual& baseWithVirtualTempR = deriveWithVirtual;
    try {
        auto& tempR = dynamic_cast<DeriveWithVirtual&>(baseWithVirtualTempR);
        cout << "dynamic_cast<DeriveWithVirtual &>(baseWithVirtualTempR) success" << endl;
        tempR.printInfo();
    } catch (bad_cast&) {
        cout << "dynamic_cast<DeriveWithVirtual &>(baseWithVirtualTempR) failed" << endl;
    }
}

static void dynamicCastTest3(DeriveWithoutVirtual* deriveWithoutVirtual) {
    // BaseWithoutVirtual' is not polymorphic. 必须有虚函数才能使用 dynamic_cast。
    /*BaseWithoutVirtual *baseWithoutVirtualTemp = deriveWithoutVirtual;
    if (auto *tempV = dynamic_cast<DeriveWithoutVirtual *>(baseWithoutVirtualTemp)) {
        cout << " dynamic_cast<DeriveWithoutVirtual *>(baseWithoutVirtualTemp) success" << endl;
    } else {
        cout << " dynamic_cast<DeriveWithoutVirtual *>(baseWithoutVirtualTemp) failed" << endl;
    }*/
}

static void dynamicCast() {
    string name1("BaseWithVirtual");
    string name2("DeriveWithVirtual");
    string name3("name1");
    string name4("name1");

    string address1("a1");
    string address2("a2");

    BaseWithVirtual baseWithVirtual(name1, 90);
    DeriveWithVirtual deriveWithVirtual(name2, 89, address1);

    BaseWithoutVirtual baseWithoutVirtual(name3, 88);
    DeriveWithoutVirtual deriveWithoutVirtual(name4, 87, address2);

    baseWithVirtual.printInfo();
    deriveWithVirtual.printInfo();
    baseWithoutVirtual.printInfo();
    deriveWithoutVirtual.printInfo();

    dynamicCastTest1(&deriveWithVirtual);
    dynamicCastTest2(deriveWithVirtual);
    dynamicCastTest3(&deriveWithoutVirtual);
}

void typeIdSample1() {
    string name1("BaseWithVirtual");
    string name2("DeriveWithVirtual");
    string name3("name1");
    string name4("name1");

    string address1("a1");
    string address2("a2");

    BaseWithVirtual baseWithVirtual(name1, 90);
    DeriveWithVirtual deriveWithVirtual(name2, 89, address1);
    BaseWithVirtual* baseWithVirtualP = &deriveWithVirtual;
    BaseWithVirtual& baseWithVirtualR = deriveWithVirtual;

    BaseWithoutVirtual baseWithoutVirtual(name3, 88);
    DeriveWithoutVirtual deriveWithoutVirtual(name4, 87, address2);

    // 在运行时比较两个对象的类型
    if (typeid(*baseWithVirtualP) == typeid(deriveWithVirtual)) {
        cout << "typeid(*baseWithVirtualP) == typeid(deriveWithVirtual) == true" << endl;
    }
    // 检测运行时类型是否是某种指定的类型
    if (typeid(*baseWithVirtualP) == typeid(DeriveWithVirtual)) {
        cout << "typeid(*baseWithVirtualP) == typeid(DeriveWithVirtual) == true" << endl;
    }
}

void typeIdSample2() {
    int iarr[]{1, 2, 4};
    float farr[]{1, 2, 4, 56};
    auto* str = new string("12345");

    auto& iinfo = typeid(iarr);
    auto& finfo = typeid(farr);
    auto& spinfo = typeid(str);
    auto& sinfo = typeid(*str);

    cout << iinfo.name() << endl;
    cout << finfo.name() << endl;
    cout << spinfo.name() << endl;
    cout << sinfo.name() << endl;
    delete str;
}

/**
 * C++中的 RTTI（Run-Time Type Identification，运行时类型识别）是一种在程序运行时确定对象类型的能力。RTTI 允许程序
 * 在运行时获取关于对象类型的信息，这在静态类型语言如 C++ 中尤为重要，因为它允许进行一些动态类型相关的操作。
 */
int main() {
    dynamicCast();
    typeIdSample1();
    typeIdSample2();
    return EXIT_SUCCESS;
}
