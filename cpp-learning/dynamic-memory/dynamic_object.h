#ifndef CPLUSPLUS_PROGRAM_DYNAMICOBJECT_H
#define CPLUSPLUS_PROGRAM_DYNAMICOBJECT_H

class DynamicObject1 {
public:
    DynamicObject1(const int a) {
        mA = a;
        mB = 100;
    }

private:
    int mA;
    int mB;

public:
    [[nodiscard]] int getTotal() const {
        return mA + mB;
    }
};

class DynamicObject2 {
public:
    DynamicObject2(const int a, const int b) {
        mA = a;
        mB = b;
    }

private:
    int mA;
    int mB;

public:
    [[nodiscard]] int getTotal() const {
        return mA + mB;
    }
};

#endif
