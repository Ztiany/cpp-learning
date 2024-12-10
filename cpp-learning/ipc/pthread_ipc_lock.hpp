#ifndef PTHREAD_IPC_LOCK
#define PTHREAD_IPC_LOCK

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <pthread.h>

using namespace std;

struct MutexData {
    pthread_mutex_t mutex;
    pthread_mutexattr_t mutexattr;
    bool initialized;
};

class ShmMutex {
    MutexData* mutexData;
    int mutexFd;
    bool mainProcess;

public:
    ShmMutex(ShmMutex& mutex) = delete;
    ShmMutex(ShmMutex&& mutex) = delete;
    ShmMutex& operator=(ShmMutex& mutex) = delete;
    ShmMutex& operator=(ShmMutex&& mutex) = delete;

    explicit ShmMutex(const string& mutexFile, const bool isMain)
        : mutexData(nullptr), mutexFd(-1), mainProcess(isMain) {
        if (!initShmMutex(mutexFile)) {
            cleanup();
            throw std::runtime_error("Failed to initialize shared mutex");
        }
    }

    ~ShmMutex() {
        cleanup();
    }

    [[nodiscard]] int lock() const {
        if (!mutexData) {
            return -1;
        }
        const int lockStatus = pthread_mutex_lock(&mutexData->mutex);
        if (lockStatus == EOWNERDEAD) {
            printf("pthread_mutex_lock() returned EOWNERDEAD\n");
            /*
             * pthread_mutex_consistent make a robust mutex consistent.
             *
             * Note: pthread_mutex_consistent() simply informs the implementation that
             * the state (shared data) guarded by the mutex has been restored to
             * a consistent state and that normal operations can now be
             * performed with the mutex.  It is the application's responsibility
             * to ensure that the shared data has been restored to a consistent
             * state before calling pthread_mutex_consistent().
            */
            if (const int result = pthread_mutex_consistent(&mutexData->mutex); result != 0) {
                printf("pthread_mutex_consistent() failed: %d\n", result);
                return result;
            }
            printf("parent Mutex is now consistent");
        }
        return lockStatus;
    }

    [[nodiscard]] int unlock() const {
        if (!mutexData) return -1;
        return pthread_mutex_unlock(&mutexData->mutex);
    }

    [[nodiscard]] int tryLock() const {
        if (!mutexData) return -1;
        const int tryLockStatus = pthread_mutex_trylock(&mutexData->mutex);

        if (tryLockStatus == EOWNERDEAD) {
            printf("pthread_mutex_trylock() returned EOWNERDEAD\n");
            if (const int result = pthread_mutex_consistent(&mutexData->mutex); result != 0) {
                printf("pthread_mutex_consistent() failed: %d\n", result);
                return result;
            }
            printf("Mutex is now consistent after tryLock\n");
        }

        return tryLockStatus;
    }

private:
    bool initShmMutex(const string& mutexFile) {
        mutexFd = open(mutexFile.c_str(), O_RDWR | O_CREAT, 0666);
        if (mutexFd == -1) {
            perror("initShmMutex.open");
            return false;
        }

        if (mainProcess) {
            if (ftruncate(mutexFd, sizeof(MutexData)) != 0) {
                perror("initShmMutex.ftruncate");
                return false;
            }
        }

        mutexData = static_cast<MutexData*>(mmap(
            nullptr,
            sizeof(MutexData),
            PROT_READ | PROT_WRITE,
            MAP_SHARED,
            mutexFd,
            0
        ));

        if (mutexData == MAP_FAILED) {
            perror("initShmMutex.mmap");
            return false;
        }

        // parent
        if (mainProcess) {
            memset(mutexData, 0, sizeof(MutexData));
            mutexData->initialized = false;

            if (pthread_mutexattr_init(&mutexData->mutexattr) != 0) {
                perror("initShmMutex.pthread_mutexattr_init");
                return false;
            }
            if (pthread_mutexattr_setpshared(&mutexData->mutexattr, PTHREAD_PROCESS_SHARED) != 0) {
                perror("initShmMutex.pthread_mutexattr_setpshared");
                return false;
            }
            if (pthread_mutexattr_setrobust(&mutexData->mutexattr, PTHREAD_MUTEX_ROBUST) != 0) {
                perror("initShmMutex.pthread_mutexattr_setrobust");
                return false;
            }
            if (pthread_mutex_init(&mutexData->mutex, &mutexData->mutexattr) != 0) {
                perror("initShmMutex.pthread_mutex_init");
                return false;
            }

            if (pthread_mutexattr_destroy(&mutexData->mutexattr) != 0) {
                perror("initShmMutex.pthread_mutexattr_destroy");
            }

            mutexData->initialized = true;
            cout << "Mutex data initialized" << endl;
            return true;
        }

        // children.
        do {
            printf("child(%d) waits for initialization.\n", getpid());
            usleep(100);
        } while (mutexData->initialized == false);
        return true;
    }

    void cleanup() {
        if (mutexData && mutexData != MAP_FAILED) {
            if (mainProcess) {
                pthread_mutex_destroy(&mutexData->mutex);
            }
            munmap(mutexData, sizeof(MutexData));
            mutexData = nullptr;
        }
        if (mutexFd != -1) {
            close(mutexFd);
            mutexFd = -1;
        }
    }
};

class ShmMutexScope {
    const ShmMutex& mutex;

public:
    explicit ShmMutexScope(const ShmMutex& mutex) : mutex(mutex) {
        if (const int result = mutex.lock(); result != 0) {
            cout << "ShmMutexScope.lock: " << result << endl;
        }
    }

    ~ShmMutexScope() {
        if (const int result = mutex.unlock(); result != 0) {
            cout << "ShmMutexScope.unlock: " << result << endl;
        }
    }
};

#endif
