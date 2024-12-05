
```c
typedef struct
{
    short           level;      /* 缓冲区"满"或者"空"的程度 */
    unsigned        flags;      /* 文件状态标志 */
    char            fd;         /* 文件描述符，用于标识当前操作的文件 */
    unsigned char   hold;       /* 如无缓冲区不读取字符 */
    short           bsize;      /* 缓冲区的大小 */
    unsigned char   *buffer;    /* 数据缓冲区的位置 */
    unsigned        ar;         /* 指针，当前的指向 */
    unsigned        istemp;     /* 临时文件，指示器 */
    short           token;      /* 用于有效性的检查 */
} FILE;

```