# C 语言多线程

C 语言在 [C11](http://www.open-std.org/JTC1/SC22/WG14/www/docs/n1570.pdf) 才提供了多线程的支持，但尴尬的是，目前无论是 Windows 还是 Linux 都没有提供对 C11 的标准实现，如果要使用多线程，可选的方案有：

1. 使用 POSIX 标准中的 pthread。
2. 使用 [TinyCThread](https://tinycthread.github.io/) 开源库，它提供对 C11 线程的标准实现，其实这个库内部是根据不同的编译环境使用不同线程 API，比如 pthread 和 MSVC 线程 API。

具体参考：

- [TinyCThread](https://tinycthread.github.io/)
- [cppreference/thread](https://en.cppreference.com/w/c/thread)
