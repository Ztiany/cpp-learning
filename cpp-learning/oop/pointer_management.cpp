/*
 * =======================================
 *  拷贝控制与外部资源管理
 * =======================================
 */

#include <string>
#include <cstddef>

class HasPtr {
public:
    // 构建一个新的对象，use 设置为 1
    explicit HasPtr(const std::string& s = std::string()) :
        ps(new std::string(s)), i(0), use(new std::size_t(1)) {}

    // copy constructor copies all three data members and increments the counter.
    HasPtr(const HasPtr& p) : ps(p.ps), i(p.i), use(p.use) {
        ++*use;
    }

    HasPtr& operator=(const HasPtr&);

    ~HasPtr();

    // move constructor takes over the pointers from its argument and makes the argument safe to delete
    HasPtr(HasPtr&& p) noexcept : ps(p.ps), i(p.i), use(p.use) {
        p.ps = nullptr;
        p.use = nullptr;
    }

    HasPtr& operator=(HasPtr&&) noexcept;

private:
    std::string* ps;
    int i;

    // 用于跟踪多个对象共享了 ps 指针
    std::size_t* use;
};

HasPtr::~HasPtr() {
    if (!use) {
        return;
    }
    if (--*use == 0) {
        // if the reference count goes to 0.
        delete ps; // delete the string
        delete use; // and the counter
    }
}

HasPtr& HasPtr::operator=(HasPtr&& rhs) noexcept {
    if (this != &rhs) {
        if (--*use == 0) {
            // do the work of the destructor.
            delete ps;
            delete use;
        }
        ps = rhs.ps; // do the work of the move constructor.
        i = rhs.i;
        use = rhs.use;
        ps = nullptr;
        use = nullptr;
    }
    return *this;
}

HasPtr& HasPtr::operator=(const HasPtr& rhs) {
    if (this == &rhs) {
        return *this;
    }

    ++*rhs.use; // increment the use count of the right-hand operand
    if (--*use == 0) {
        // then decrement this object's counter
        delete ps; // if no other users
        delete use; // free this object's allocated members
    }
    ps = rhs.ps; // copy data from rhs into this object
    i = rhs.i;
    use = rhs.use;
    return *this; // return this object
}

HasPtr f(const HasPtr& hp) {
    // HasPtr passed by value, so it is copied
    HasPtr ret;
    ret = hp; // assignment copies the given HasPtr
    // process ret
    return ret; // ret and hp are destroyed
}

int main() {
    const HasPtr h("hi mom!");
    HasPtr h2 = h; // no new dynamic_memory is allocated,
    // h and h2 share the same underlying string
}
