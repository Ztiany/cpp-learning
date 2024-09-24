#[[
变量引用：

    1. 变量引用(variable reference)类似于很多编程语言提供的字符串插值(string interpolation)语法，可以在参数内容中插入一个变量的值。
    2. CMake 变量引用形式为 ${变量}，即在$符号后面使用一对花括号包裹变量名。
    3. CMake 变量引用可用在引号参数和非引号参数中，CMake 会将其替换为对应变量的值。
    4. 若变量名未定义，CMake 并不会报错，而是将其替换为空字符串。另外，变量引用还支持嵌套的递归引用，
]]
set(var_a "我是变量 A")
set(var_b a)
# 输出：我是变量A
message(${var_${var_b}})


#[[
CMake 变量：

    CMake 数据类型总是文本型的，只不过在使用时，文本型的变量可能被一些命令解释成数值、列表等，以实现更加丰富的功能。

变量的分类：

    - 普通变量：大多数变量都是普通变量，它们具有特定的作用域。
    - 缓存变量：就是能够被缓存起来的变量，会被持久化到缓存文件 CMakeCache.txt。
    - 环境变量：操作系统中的环境变量，因此它对于 CMake 进程而言具有全局的作用域。

变量作用域：

    - 函数作用域。在用户自定义的函数命令中会有一个独立的作用域。默认情况下，函数内定义的变量只在函数内部或函数中调用的其他函数中可见。
    - 目录作用域。对于 CMake 的目录程序而言，每一个目录层级，都有它的一个作用域。子目录的程序被执行前，会先将父目录作用域中的所有变
      量复制一份到子目录的作用域中。因此，子目录的程序可以访问但无法修改父目录作用域中的变量。

保留标识符：

    ● 以“CMAKE_”开头的名称（不区分大小写）；
    ● 以“_CMAKE_”开头的名称（不区分大小写）；
    ● 下画线“_”加上 CMake 中任意一个预定义命令的名称，如“_message”。

常见的预定义变量：

    ● CMAKE_ARGC 表示 CMake 脚本程序在被 cmake -P 命令行调用执行时，命令行传递的参数个数。
    ● CMAKE_ARGV0、CMAKE_ARGV1 表示 CMake 脚本程序在被命令行调用执行时，命令行传递的第一个、第二个参数。如果有更多参数，可以以此类推增加变量名称末尾的数值来获得。
    ● CMAKE_COMMAND 表示 CMake 命令行程序所在的路径。
    ● CMAKE_HOST_SYSTEM_NAME 表示宿主机操作系统（运行 CMake 的操作系统）名称。
    ● CMAKE_SYSTEM_NAME 表示 CMake 构建的目标操作系统名称。默认与宿主机操作系统一致，一般用于交叉编译时，由开发者显式设置。
    ● CMAKE_CURRENT_LIST_FILE 表示当前运行中的 CMake 程序对应文件的绝对路径。
    ● CMAKE_CURRENT_LIST_DIR 表示当前运行中的 CMak e程序所在目录的绝对路径。
    ● MSVC 表示在构建时 CMake 当前使用的编译器是否为 MSVC。
    ● WIN32 表示当前目标操作系统是否为 Windows。
    ● APPLE 表示当前目标操作系统是否为苹果操作系统（包括 macOS、iOS、tvOS、watchOS等）。
    ● UNIX 表示当前目标操作系统是否为 UNIX 或类 UNIX 平台（包括 Linux、苹果操作系统及 Cygwin 平台）。
]]
message("CMAKE_ARGC: " ${CMAKE_ARGC})
message("OS: " ${CMAKE_HOST_SYSTEM_NAME})


#[[
定义变量：set 命令可以用于定义或赋值一个普通变量、缓存变量或环境变量。

    因为 CMake 并不强制要求变量在定义后才能读取。在 CMake 中，读取未定义变量的值不会产生错误，而是会读取到空字符串，因此“定义”和“赋值”往往不必特别区分。

set 命令语法：set(<变量> <值>... [PARENT_SCOPE])

    1. 第一个参数写变量名，紧接着写变量的值即可。
    2. 变量的值可以由若干参数来提供，这些参数会被分号分隔连接成一个列表的形式，作为最终的变量值。
    3. 值参数也可以被省略，此时，该变量会从当前作用域中移除，相当于对该变量调用 了unset 命令。
    4. 还可以通过可选参数 PARENT_SCOPE 将变量定义到父级作用域中。对于目录而言，就是将变量定义到
       父目录作用域中；对于函数而言，就是将变量定义到函数调用者所在的作用域中。
]]
set(VariableA A)
set(VariableList A B C)

# 定义一个函数用来设置一些变量，以测试变量的作用域。
function(setVariables)
    set(VariableA "A in function: setVariables")
    set(VariableB "B in function: setVariables")
    set(VariableC "C in function: setVariables" PARENT_SCOPE)
endfunction()

setVariables()
message("VariableA: " ${VariableA})
message("VariableB: " ${VariableB})
message("VariableC: " ${VariableC})
message("VariableList: " ${VariableList})


#[[
定义缓存变量：set(<变量> <值>... CACHE <变量类型> <变量描述> [FORCE])

    1. 定义缓存变量的命令比定义普通变量的命令多了 CACHE 和 FORCE 参数，以及一些与变量相关的元信息——类型和描述。
    2. 因为缓存变量具有全局的作用域，也就不需要 PARENT_SCOPE 参数。

变量类型：

    - BOOl
    - FILEPATH
    - PATH
    - STRING
    - INTERNAL

Force 参考：

    - FORCE 可选参数用于强制覆盖缓存变量的值。默认情况下，如果缓存变量已经被定义，CMake 会忽略后续对该缓存变量的
      set 赋值命令，除非这个 set 命令中指定了 FORCE 参数。

布尔类型的变量设置：布尔型缓存变量还可以使用 option 命令定义：

    option(<变量> <变量描述> [<ON|OFF>])

覆盖和定义缓存变量：

    - 缓存变量除了可以通过在程序中使用 set 命令和 option 命令定义外，还可以通过直接修改持久化缓存文件 CMakeCache.txt 的方式来定义或覆盖其值。
    - 另外，CMake 命令行工具的 -D 参数也可以用于定义或覆盖缓存变量的值：
        -D <变量>:<缓存变量类型>=<值>
        -D <变量>=<值>

当缓存参数为 PATH/FILEPATH 时：

    - 当缓存变量是 PATH 或 FILEPATH 类型，且通过命令行为定义的变量值是一个相对路径时，set 命令会将这个相对路径根据当前目录转换为绝对路径。

# 引用缓存变量：

    - 引用缓存变量有一种特殊语法：$CACHE{...}。
    - 同名的普通变量和缓存变量同时存在时，普通变量引用语法优先匹配普通变量。
]]
message("No examples of cache variables.")


#[[
定义环境变量：

    - 环境变量具有全局作用域，不支持使用参数列表来定义值，也没有其他信息。
    - 通过 CMake 的 set 命令定义的环境变量只会影响当前的 CMake 进程，不会影响到父进程或系统的环境变量配置。
    - 命令中的值参数虽然不能是多个参数构成的列表，但仍然是可选的。如果不填写值参数，CMake 则会将对应环境变量的值清空。
]]
message("main \$ENV{PATH}: $ENV{PATH}")
set(ENV{PATH} "path")
message("main \$ENV{PATH}: $ENV{PATH}")
# execute_process 会捕获子进程的标准输出，默认不输出到终端中，因此需要借助 OUTPUT_VARIABLE 参数获取捕获的标准输出。
execute_process(
        COMMAND ${CMAKE_COMMAND} -P "subscript/setenv.cmake"
        OUTPUT_VARIABLE out
)
# 将标准输出获取到了 out 变量中并输出到终端。
message("${out}")
message("main \$ENV{PATH}: $ENV{PATH}")