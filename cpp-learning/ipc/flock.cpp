/*
 * =======================================
 *  flock
 * =======================================
 */

#include "flock.hpp"
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define FLOCK_TEST_FILE "flock.txt"

static void doSharedMemoryEdition(char* shared, FileLock& lock) {
    ExclusiveFileLockScope mutexScope(lock);
    const int current = atoi(shared);
    sprintf(shared, "%d", current + 1);
}

static void truncateFile(const int fd, FileLock& lock) {
    ExclusiveFileLockScope mutexScope(lock);

    struct stat st = {};
    if (stat(FLOCK_TEST_FILE, &st) != 0) {
        perror("stat");
        return;
    }

    if (st.st_size == 0) {
        if (ftruncate(fd, 100) != 0) {
            perror("ftruncate");
        } else {
            cout << "File initialized with size 100 bytes" << endl;
        }
    }
}

static void commonWork(const string& host) {
    const int fd = open(FLOCK_TEST_FILE, O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("open");
    }
    FileLock fileLock(fd);

    truncateFile(fd, fileLock);
    cout << "work of " << host << " started!" << endl;

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
        return;
    }

    for (int i = 0; i < 10 * 10000; i++) {
        doSharedMemoryEdition(number, fileLock);
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
    commonWork(string("child"));
}

static void doParentWork(const __pid_t child) {
    cout << "do parent work" << endl;
    commonWork(string("parent"));

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