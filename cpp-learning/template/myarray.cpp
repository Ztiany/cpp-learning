/*
 * =======================================
 *  模板编程
 * =======================================
 */

#include<iostream>

using namespace std;

template <class T>
class MyArray {
public:
    explicit MyArray(int capacity) {
        this->mCapacity = capacity;
        this->mSize = 0;
        this->pAddr = new T[this->mCapacity];
    }

    MyArray(const MyArray& arr) {
        this->mSize = arr.mSize;
        this->mCapacity = arr.mCapacity;
        this->pAddr = new T[this->mCapacity];
        // copy elements
        for (int i = 0; i < this->mSize; i++) {
            this->pAddr[i] = arr.pAddr[i];
        }
    }

    T& operator[](int index) {
        return this->pAddr[index];
    }

    MyArray& operator=(const MyArray& arr) {
        // handle self-assignment.
        if (this == &arr) {
            return *this;
        }

        if (this->pAddr != nullptr) {
            delete[] this->pAddr;
        }
        this->mSize = arr.mSize;
        this->mCapacity = arr.mCapacity;

        this->pAddr = new T[this->mCapacity];
        for (int i = 0; i < this->mSize; i++) {
            this->pAddr[i] = arr.pAddr[i];
        }
        return *this;
    }

    void PushBack(T& data) {
        // 判断容器中是否有位置
        if (this->mSize >= this->mCapacity) {
            return;
        }

        // 调用拷贝构造操作符：
        //  1. 对象元素必须能够被拷贝。
        //  2. 容器都是值寓意，而非引用寓意，向容器中放入元素，都是放入的元素的拷贝份。
        //  3  如果元素的成员有指针，注意深拷贝和浅拷贝问题。
        this->pAddr[this->mSize] = data;
        ++this->mSize;
    }

    void PushBack(T&& data) {
        // 判断容器中是否有位置
        if (this->mSize >= this->mCapacity) {
            return;
        }

        // 调用移动拷贝操作符。
        this->pAddr[this->mSize] = std::move(data);
        ++this->mSize;
    }

    [[nodiscard]] int Size() const {
        return this->mSize;
    }

    ~MyArray() {
        if (this->pAddr != nullptr) {
            delete[] this->pAddr;
        }
    }

private:
    // 一共可以容下多少个元素
    int mCapacity;
    // 当前数组有多少元素
    int mSize;
    // 保存数据的首地址
    T* pAddr;
};

void test01() {
    MyArray<int> my_array(20);
    int a = 10, b = 20, c = 30, d = 40;
    my_array.PushBack(a);
    my_array.PushBack(b);
    my_array.PushBack(c);
    my_array.PushBack(d);

    my_array.PushBack(100);
    my_array.PushBack(200);
    my_array.PushBack(300);

    for (int i = 0; i < my_array.Size(); i++) {
        cout << my_array[i] << " ";
    }
    cout << endl;
}

class Person {
public:
    Person() noexcept {
        cout << "Person()" << endl;
    }

    Person(Person& person) {
        cout << "Person copy constructor" << endl;
    }

    Person& operator=(const Person& obj) {
        cout << "Person copy assignment" << endl;
        return *this;
    }

    Person& operator=(Person&& obj) noexcept {
        cout << "Person move assignment" << endl;
        return *this;
    }

    Person(Person&& person) noexcept {
        cout << "Person move constructor" << endl;
    }
};

void test02() {
    Person p1, p2;
    MyArray<Person> arr(10);
    arr.PushBack(p1);
    arr.PushBack(Person());
}

int main() {
    test01();
    test02();
    return 0;
}
