/*
 * =======================================
 *  Posix Threading: Inter process Lock.
 * =======================================
 */

#include <sys/wait.h>
#include <sys/stat.h>
#include "pthread_ipc_lock.hpp"

#define LOCK_FILE "pthread_mutex_lock.lock"

#define SHARED_FILE "pthread_test_shared_file.txt"

static void doSharedMemoryEdition(char* shared, const ShmMutex& mutex) {
    ShmMutexScope mutexScope(mutex);
    const int current = atoi(shared);
    sprintf(shared, "%d", current + 1);
}

static void truncateFile(const int fd, const ShmMutex& mutex) {
    struct stat st = {};

    ShmMutexScope mutexScope(mutex);

    if (stat(SHARED_FILE, &st) != 0) {
        perror("stat");
    }
    if (st.st_size == 0) {
        if (ftruncate(fd, 100) != 0) {
            perror("ftruncate");
        }
        cout << "ftruncate: " << st.st_size << endl;
    }
}

static void commonWork(const string& host, const ShmMutex& shmMutex) {
    cout << "work of " << host << " started!" << endl;

    const int fd = open(SHARED_FILE, O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("open");
    }
    truncateFile(fd, shmMutex);

    const auto number = static_cast<char*>(mmap(
        nullptr,
        100,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        fd,
        0
    ));

    if (number == MAP_FAILED) {
        perror("mmap");
    }

    for (int i = 0; i < 100 * 10000; i++) {
        doSharedMemoryEdition(number, shmMutex);
    }

    if (munmap(number, 100) != 0) {
        perror("munmap");
    }

    if (close(fd) != 0) {
        perror("close");
    }

    cout << "work of " << host << " finished!" << endl;
}

static void doChildWork() {
    cout << "do child work" << endl;
    const ShmMutex shmMutex(string(LOCK_FILE), false);

    commonWork(string("child"), shmMutex);
}

static void doParentWork(const __pid_t child) {
    cout << "do parent work" << endl;
    const ShmMutex shmMutex(string(LOCK_FILE), true);

    commonWork(string("parent"), shmMutex);

    int status = 0;
    if (waitpid(child, &status, 0) == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
    }
    if (WIFEXITED(status)) {
        printf("Child process exited with status %d\n", WEXITSTATUS(status));
    } else {
        printf("Child process terminated abnormally\n");
    }
}

int main() {
    if (const __pid_t pid = fork(); pid == -1) {
        perror("fork");
    } else if (pid == 0) {
        doChildWork();
    } else {
        doParentWork(pid);
    }
    return 0;
}
