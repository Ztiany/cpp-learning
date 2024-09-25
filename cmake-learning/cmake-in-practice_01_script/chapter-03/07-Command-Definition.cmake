#[[
宏定义：

    macro(<宏名> [<参数1>...])
        <命令>...
    endmacro()

注意:

    - 宏就是把它所包含的命令序列直接复制到它被调用的地方来执行，因此宏本身不会拥有一个作用域，而是与调用上下文共享作用域。
    - 在 CMake 中，命令的名称不区分大小写，宏作为一种命令，其名称也不例外。不过，建议调用时书写的宏名与定义时的宏名保持一致。
]]
message(============宏定义============)

macro(my_macro a b)
    set(result "参数a: ${a}, 参数b: ${b}")
endmacro()

my_macro(x y)
message("${result}") # 输出：参数a: x, 参数b: y

MY_macro(A;B)
message("${result}") # 输出：参数a: A, 参数b: B

MY_MACRO(你 好)
message("${result}") # 输出：参数a: 你, 参数b: 好

#[[
函数定义：

    function(<函数名> [<参数1>...])
        <命令>...
    endfunction()

函数会产生一个新的作用域，因此函数内部直接使用set命令定义的变量是不能被外部访问的。为了实现这个目的，必须为 set 命令指定 PARENT_SCOPE 参数，使得变量定义到外部作用域。
]]
message(============函数定义============)

function(my_func a b)
    set(result "参数a: ${a}, 参数b: ${b}" PARENT_SCOPE)
endfunction()
my_func(x y)
message("${result}") # 输出：参数a: x, 参数b: y
MY_func(A;B)
message("${result}") # 输出：参数a: A, 参数b: B
MY_FUNC(你 好)
message("${result}") # 输出：参数a: 你, 参数b: 好


#[[
引用形式参数：

    1. 形式参数(formal parameter)就是在宏或函数定义时指定的参数。
    2. 在宏或函数定义的内部命令序列中，可以通过变量引用的语法引用形式参数的名称，从而获得调用时传递过来的实际参数的值。


列表或索引访问参数：除了直接引用形式参数外，CMake 的宏和函数还都支持使用列表或索引来访问某一个参数。

    ● ${ARGC} 表示参数的个数；
    ● ${ARGV} 表示完整的实际参数列表，其元素为用户传递的每一个参数；
    ● ${ARGN} 表示无对应形式参数的实际参数列表，其元素为从第 (N+1) 个用户传递的参数开始的每一个参数，N 为函数或宏定义中形式参数的个数；
    ● ${ARGV0}、${ARGV1}、${ARGV2} 依次表示第1个、第 2 个、第3个实际参数的值，以此类推。
]]
message(============引用形式参数============)

macro(my_macro p)
    message("ARGC: ${ARGC}")
    message("ARGV: ${ARGV}")
    message("ARGN: ${ARGN}") # 排除 p 之外的其他参数。
    message("ARGV0: ${ARGV0}, ARGV1: ${ARGV1}")
endmacro()

function(my_func p)
    message("ARGC: ${ARGC}")
    message("ARGV: ${ARGV}")
    message("ARGN: ${ARGN}")
    message("ARGV0: ${ARGV0}, ARGV1: ${ARGV1}")
endfunction()

my_macro(x y z)
my_func(x y z)


#[[
参数的设计与解析：

    - CMake 的命令参数往往由两部分组成：一部分是用户提供的参数值；另一部分则是一些关键字，用于构成参数的结构。这些关键字的名称往往由全大写的字母组成。
    - 这些关键字可以分为如下三种类型。
        ● 开关选项(option)：调用者可以通过指定该参数来启用某个选项。开关选项参数可以理解为一种表示布尔值的参数。
        ● 单值参数关键字(one-value keyword)：它的后面会且仅会跟随一个参数值，相当于键值映射，一个关键字对应一个实际参数值。
        ● 多值参数关键字(multi-value keyword)：它的后面可以跟随多个参数值，相当于一个接受列表的参数。这类似其他编程语言中的可变数组型参数。

cmake_parse_arguments 命令正是用于解析符合这个规范的参数。

    cmake_parse_arguments(
        <结果变量前缀名>
        <开关选项关键字列表> <单值参数关键字列表> <多值参数关键字列表>
        <将被解析的参数>...
    )

cmake_parse_arguments 针对函数优化的形式：

    由于 cmake_parse_arguments 命令的通用形式存在一些缺陷，它还提供了如下针对函数优化的形式，可以解析包含特殊字符的参数：

        cmake_parse_arguments(PARSE_ARGV
        <N>
            <结果变量前缀名>
            <开关选项关键字列表> <单值参数关键字列表> <多值参数关键字列表>
        )

    该命令形式只能在函数中使用，不支持在宏中使用。它直接对每一个函数参数进行解析，因此无须通过列表的形式传递函数参数。
    <N> 是一个从 0 开始的整数，表示从函数的第几个实际参数开始解析参数，换句话说，前 N 个参数都是不需要关键字、需要调用者直接依次传参的参数。
    该形式中的其他参数与通用形式中的对应参数含义完全一致。

两个特殊的结果变量：

    cmake_parse_arguments 除了将解析的参数存放到对应关键字的结果变量中，还会将一些未能解析的参数、没有提供值的关键字等信息存放到另外两个特殊的结果变量中：

        ● <结果变量前缀名>_UNPARSED_ARGUMENTS 存放所有未能解析到某一关键字中的实际参数值；
        ● <结果变量前缀名>_KEYWORDS_MISSING_VALUES 存放所有未提供实际参数值的关键字名称。

]]
message(============参数的设计与解析============)

function(abc_f)
    cmake_parse_arguments(abc "ENABLE" "VALUE" "" ${ARGN})
    message("abc_ENABLE: ${abc_ENABLE}")
    message("abc_VALUE: ${abc_VALUE}")
endfunction()

abc_f(VALUE a ENABLE)


message(============两个特殊的结果变量============)

function(my_copy_func)
    set(options OVERWRITE MOVE)
    set(oneValueArgs DESTINATION)
    set(multiValueArgs PATHS)
    cmake_parse_arguments(
            PARSE_ARGV 0
            my
            "${options}" "${oneValueArgs}" "${multiValueArgs}"
    )
    message("my_UNPARSED_ARGUMENTS: ${my_UNPARSED_ARGUMENTS}")
    message("my_KEYWORDS_MISSING_VALUES: ${my_KEYWORDS_MISSING_VALUES}")
endfunction()

my_copy_func(COPY "../dir" DESTINATION PATHS)


message(============实例：复制文件命令============)
function(my_copy_func)
    message("ARGN: ${ARGN}")
    set(options OVERWRITE MOVE)
    set(oneValueArgs DESTINATION)
    set(multiValueArgs PATHS)
    cmake_parse_arguments(
            my
            "${options}" "${oneValueArgs}" "${multiValueArgs}"
            ${ARGN}
    )
    message("OVERWRITE:\t${my_OVERWRITE}")
    message("MOVE:\t\t${my_MOVE}")
    message("DESTINATION:\t${my_DESTINATION}")
    message("PATHS: \t\t${my_PATHS}")
    message("---")
endfunction()

my_copy_func(DESTINATION "../.." PATHS "1.txt" "2.txt" OVERWRITE)
my_copy_func(MOVE DESTINATION "../../.." PATHS "3.txt" "4.txt")
my_copy_func(DESTINATION "../folder;name" PATHS 1.txt;2.txt)


#[[
宏和函数的区别

    - 执行上下文和作用域：
        宏和函数最明显的区别就是作用域。宏会与调用上下文共享作用域，因此它的执行上下文就是调用上下文。
        宏相当于将其定义的命令序列直接复制到调用上下文中去执行，这一过程可以称为“宏展开”。
    - return 命令：
        CMake 目录或文件的执行。如果在宏中调用 return，并不只是宏的执行被中断，宏所在的函数、CMake 目录或文件也会被中断。
        因此，在宏中一定要避免使用 return 等影响父作用域的命令。
    - 返回值：
        CMake 命令没有返回值这一概念，定义外部可见的变量其实是 CMake 函数“返回值”的形式。 CMake 中的 return 命令并不负责返回值，仅用于结束当前执行上下文。
]]
message(============宏和函数的区别============)
message("no examples")


#[[
预定义变量：

    ● CMAKE_CURRENT_FUNCTION，值为当前函数名称；
    ● CMAKE_CURRENT_FUNCTION_LIST_DIR，值为定义当前函数的CMake程序文件所在的目录；
    ● CMAKE_CURRENT_FUNCTION_LIST_FILE，值为定义当前函数的CMake程序文件的完整路径；
    ● CMAKE_CURRENT_FUNCTION_LIST_LINE，值为当前函数

参数访问：

    1. 在函数中，包括形式参数、ARGC、ARGV、ARGN 等都是真正的 CMake 变量，且定义在当前函数的作用域内。
    2. 但在宏中，由于没有独立的作用域，这些用于访问参数的符号并非真正的变量，否则会污染调用上下文。
    3. CMake 在展开宏时，会对宏的命令序列进行预处理，对引用这些符号的地方直接进行文本替换。这就带来一些问题：

            在宏中，不能直接将这些访问参数的符号作为变量条件用于条件语法，也不能利用变量嵌套引用语法访问这些符号。
]]
message(============参数访问============)

macro(my_macro p)
    message("-- my_macro --")
    message("p = " ${p})
    if (p) # 不走这里
        message("p为真")
    endif ()

    if (p STREQUAL "p")
        message("p为真")
    endif ()
    set(i 1)
    message("ARGV i: ${ARGV${i}}")

endmacro()

function(my_func p)
    message("-- my_func --")
    if (p)
        message("p为真")
    endif ()
    set(i 1)
    message("ARGV i: ${ARGV${i}}")
endfunction(my_func)

my_macro(ON x)
my_func(ON x)