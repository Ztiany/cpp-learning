//=======================================================================
//
// chapter01：一个完整的 C 程序
//
//=======================================================================

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>

// 定义用到的宏常量与宏函数；
#define BOOL_TRUE 1
#define BOOL_FALSE 0
#define typename(x) _Generic((x), \
  unsigned short: "unsigned short int", \
  unsigned long: "unsigned long int", \
  default: "unknown") // 这里 C11 引入的宏泛型

// 定义枚举类型 IP_ADDR_TYPE，用于表示联合中生效的字段；
typedef enum { Host, IP } IP_ADDR_TYPE;

// 定义结构 CONN；
typedef struct {
    size_t id;
    uint16_t port;
    bool closed;
    IP_ADDR_TYPE addr_type;
    union {
        char host_name[256];
        char ip[24];
    };
} CONN;

// 定义函数 findAddr，用于打印 CONN 对象的信息；
inline static const char *findAddr(const CONN *pip) {
    // 运行时断言，判断传入的 CONN 指针是否有效；
    assert(pip != NULL);
    return pip->addr_type == Host ? pip->host_name : pip->ip;
}

// 入口函数；
int main(int argc, char *argv[]) {
    // 静态断言，判断 CONN 对象的大小是否符合要求；
    static_assert(sizeof(CONN) <= 0x400, "the size of CONN object exceeds limit.");

    // 构造一个数组，包含三个 CONN 对象；
    const CONN conns[] = {
            [2] = {1, 80, BOOL_TRUE, IP, {.ip = "127.0.0.1"}},
            [0] = {2, 8080, BOOL_FALSE, IP, {.ip = "192.168.1.1"}},
            {3, 8088, BOOL_FALSE, Host, {.host_name = "http://localhost/"}}
    };

    // 遍历上述 CONN 数组，并打印其中的内容；
    for (size_t i = 0; i < (sizeof(conns) / sizeof(CONN)); ++i) {
        printf(
                "Port: %d\n"
                "Host/Addr: %s\n"
                "Internal type of `id` is: %s\n\n",
                conns[i].port,
                findAddr(&conns[i]),
                typename(conns[i].id)
        );
    }

    return EXIT_SUCCESS;
}