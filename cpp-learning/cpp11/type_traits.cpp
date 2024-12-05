/*
<type_traits> 是 C++ 标准库的一部分，它最早出现在 C++11 标准中。<type_traits> 头文件提供了一组编译时检查的工具，用于
类型特性查询和类型转换，这些工具帮助开发者编写更通用和更安全的模板代码。

<type_traits> 中包含了许多有用的模板，例如：

        std::is_integral：检查类型是否为整数类型。
        std::is_floating_point：检查类型是否为浮点类型。
        std::is_same：检查两个类型是否相同。
        std::is_base_of：检查一个类型是否是另一个类型的基类。
        std::conditional：一个编译时的条件选择器。
        std::decay：去除类型修饰，获取其 Decayed Type。

C++17 标准在此基础上增加了一些新的工具，比如 if constexpr 和 std::void_t，以及对 auto 的支持，使得 type_traits 的
使用更加方便。if constexpr 允许在编译时根据 constexpr 条件来选择代码路径，而 std::void_t 用于在类型特性表达式中创建
一个空类型，这在某些模板元编程技巧中非常有用。总的来说，<type_traits> 是 C++11 引入的，C++17 进一步增强了它的功能。
*/