/*
 * =======================================
 *  单例设计模式
 * =======================================
 */

#include <mutex>

class Instance {
public:
    static Instance* getInstance() {
        static std::mutex mutex;
        /*
         * std::lock_guard是 C++11 标准库中引入的一个模板类，它用于管理互斥锁（mutex）的生命周期，确保即使在发生异常
         * 时也能自动释放锁。std::lock_guard 是一种 RAII（Resource Acquisition Is Initialization）工具，它在
         * 构造时自动获取互斥锁，并在析构时自动释放互斥锁。
         */
        std::lock_guard lock(mutex);
        if (!instance) {
            instance = new Instance();
        }
        return instance;
    }

private:
    static Instance* instance;
};

Instance* Instance::instance = nullptr;

int main() {
    // 获取单例对象
    Instance* obj = Instance::getInstance();
    // ...
    return 0;
}
