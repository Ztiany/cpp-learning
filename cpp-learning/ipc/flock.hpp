#ifndef IPC_FLOCK_H
#define IPC_FLOCK_H

#include <sys/file.h>
#include <iostream>

using namespace std;

enum LockType {
    SharedLockType,
    ExclusiveLockType,
};

class FileLock {
    int fd;

    [[nodiscard]] bool isFdValid() const {
        return fd != -1;
    }

public:
    FileLock(FileLock& fileLock) = delete;
    FileLock(FileLock&& fileLock) = delete;
    FileLock& operator=(FileLock& fileLock) = delete;
    FileLock& operator=(FileLock&& fileLock) = delete;

    explicit FileLock(const int _fd): fd(_fd) {}

    [[nodiscard]] bool lock(const LockType lockType) const {
        if (!isFdValid()) {
            return false;
        }
        /*
         * see: https://linux.die.net/man/2/flock.
         *
         * LOCK_SH  Place a shared lock.  More than one  process  may  hold  a shared lock for a
         *          given file at a given time.
         * LOCK_EX  Place an exclusive lock.  Only one process may hold an ex‐clusive lock for a
         *          given file at a given time.
         * LOCK_UN  Remove an existing lock held by this process.
         * LOCK_NB  A call to flock() may block if an incompatible lock is held by another process.
         *          To make a nonblocking request, include LOCK_NB (by ORing) with any of the above
         *          operations.
         */
        const int result = flock(fd, lockType == SharedLockType ? LOCK_SH : LOCK_EX);
        if (result != 0) {
            perror("flock");
            return false;
        }
        return true;
    }

    [[nodiscard]] bool tryLock(const LockType lockType) const {
        if (!isFdValid()) {
            return false;
        }
        const int result = flock(
            fd, lockType == SharedLockType ? LOCK_SH | LOCK_NB : LOCK_EX | LOCK_NB
        );
        if (result != 0) {
            perror("flock");
            return false;
        }
        return true;
    }

    [[nodiscard]] bool unlock() const {
        if (!isFdValid()) {
            return false;
        }
        if (const int result = flock(fd, LOCK_UN); result != 0) {
            perror("flock.unlock");
            return false;
        }
        return true;
    }
};


class SharedFileLockScope {
    FileLock& lock;

public:
    explicit SharedFileLockScope(FileLock& mutex) : lock(mutex) {
        if (!lock.lock(SharedLockType)) {
            cout << "SharedFileLockScope.lock error" << endl;
        }
    }

    ~SharedFileLockScope() {
        if (!lock.unlock()) {
            cout << "SharedFileLockScope.unlock error" << endl;
        }
    }
};

class ExclusiveFileLockScope {
    FileLock& lock;

public:
    explicit ExclusiveFileLockScope(FileLock& mutex) : lock(mutex) {
        if (!lock.lock(ExclusiveLockType)) {
            cout << "ExclusiveFileLockScope.lock error" << endl;
        }
    }

    ~ExclusiveFileLockScope() {
        if (!lock.unlock()) {
            cout << "ExclusiveFileLockScope.unlock error" << endl;
        }
    }
};

#endif