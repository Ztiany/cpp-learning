cmake_minimum_required(VERSION 3.20)

#[[
条件语法：

    常量条件
    变量条件
    字符串条件

常量条件：

    - 见图

变量条件和字符串条件：

    - 如果条件中仅包含一个字符串，且这个字符串不是真值常量或假值常量，那么它还有可能是一个变量的名称。
    - 如果以这个字符串为名的变量确实存在，则它是一个变量条件，否则是一个字符串条件。
        ● 如果条件中的字符串是一个变量的名称，且这个变量的值不是一个假值常量，那么条件为真。
        ● 在其他情况下（如指定变量的值为假值常量或变量未定义时），条件为假。

if 条件分支：

    if(<条件>)
        <命令>...
    elseif(<条件>)
        <命令>...
    else()
        <命令>...
    endif()
]]
message(============if " " 条件分支============)
if (ABC)
else ()
    message("ABC不是一个已定义的变量，因此条件为假")
endif ()

set(a "XYZ")
set(b "0")
set(c "a-NOTFOUND")
if (a)
    message("a是一个变量，其值非假值常量，因此条件为真")
endif ()

if (b)
else ()
    message("b是一个变量，其值为假值常量，因此条件为假")
endif ()

if (c)
else ()
    message("c是一个变量，其值为假值常量，因此条件为假")
endif ()

# 注意这个奇怪的变量：这个变量名本身是一个真值常量，而其定义的值又是一个假值常量。
set(on "OFF")
if (on)
    message("ON")
else ()
    message("OFF")
endif ()

if (${on})
    message("ON")
else ()
    message("OFF")
endif ()


#[[
while 判断循环：

    while(<条件>)
        <命令>...
    endwhile()
]]
message(============while " " 判断循环============)
set(A B)
while (${A} STREQUAL B)
    message("running in a while.")
    set(A A)
endwhile ()


#[[
简单列表遍历：

    foreach(<循环变量> <循环项的列表>)
        <命令>...
    endforeach()
]]
message(============简单列表遍历============)
foreach (x A;B;C D E F)
    message("x: ${x}")
endforeach ()

message("---")

set(list X;Y;Z)
foreach (x ${list})
    message("x: ${x}")
endforeach ()


#[[
区间遍历：
    foreach(<循环变量> RANGE [<起始值>] <终止值> [<步进>])
]]
# 从 2 开始遍历到 11，步长为 2.
message(============区间遍历============)
foreach (x RANGE 2 11 2)
    message("x: ${x}")
endforeach ()


# 高级列表遍历：foreach(<循环变量> IN [LISTS [<列表变量名的列表>]] [ITEMS [<循环项的列表>]])
#[[
“高级列表遍历”是“简单列表循环”的超集：如果上述循环的参数中省略LISTS部分，仅保留ITEMS部分，那么它与“简单列表遍历”是等价的。即下面两种写法等价：

    foreach(<循环变量> IN ITEMS <循环项的列表>)
    foreach(<循环变量> <循环项的列表>)

简而言之：LISTS 后面跟着的是一个个变量名，代表不同的列表；ITEMS 后面跟着的则是一个个列表元素。
]]
message(============高级列表遍历============)
set(a A;B)
set(b C D)
set(c "E F")
set(d G;H I)
set(e "")
foreach (x IN LISTS a b c;d;e ITEMS a b c;d;e)
    message("x: ${x}")
endforeach ()


#[[
打包遍历：

    foreach(<循环变量>... IN ZIP_LISTS <列表变量名的列表>)

说明：

    - 打包遍历中的 <列表变量名的列表> 也是一个变量名称列表。打包遍历会对每一个列表变量同时进行遍历，并把各个列表当次遍历到的的元素赋值给不同的循环变量。
    - 类似 Python 语言中的 zip 函数。
]]
message(============打包遍历============)

set(a A;B;C)
set(b 0;1;2)
set(c X;Y)
foreach (x IN ZIP_LISTS a;b c)
    message("x_0: ${x_0}, x_1: ${x_1}, x_2: ${x_2}")
endforeach ()

foreach (x y z IN ZIP_LISTS a b;c)
    message("x:   ${x}, y:   ${y}, z:   ${z}")
endforeach ()

#[[
跳出和跳过循环：

    - break()
    - continue()
]]
message(============跳出和跳过循环============)


#[[
逻辑运算：条件语法中可以包含与(AND)、或(OR)、非(NOT)三种逻辑运算，参与运算的也是符合条件语法的参数：

    if(<条件1> AND <条件2>)
    if(<条件1> OR <条件2>)
    if(NOT <条件>)
]]
message(============逻辑运算============)
if (NOT OFF)
    message("NOT OFF为真")
endif ()

if (ON AND YES)
    message("ON AND YES为真")
endif ()

if (TRUE AND NOTFOUND)
else ()
    message("TRUE AND NOTFOUND为假")
endif ()

if (A-NOTFOUND OR YES)
    message("A-NOTFOUND OR YES为真")
endif ()


#[[
单参数条件：

    单参数条件，即根据单个参数进行判断的条件，一般用于存在性判断和类型判断。
]]
message(============单参数条件============)

set(a 1)
if(DEFINED a)
    message("DEFINED a为真")
endif()

if(CACHE{b})
else()
    message("CACHE{b}为假")
endif()

if(COMMAND set)# 如果有 set 命令
    message("COMMAND set为真")
endif()

if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/逻辑运算.cmake")
    message("EXISTS \"${CMAKE_CURRENT_LIST_DIR}/逻辑运算.cmake\"为真")
endif()

#[[
双参数条件：双参数条件通过两个参数的取值来决定条件是否为真，一般用于比较关系的判断。

    - 数值比较
        if(<字符串|变量> LESS <字符串|变量>) # 小于
        if(<字符串|变量> GREATER <字符串|变量>) # 大于
        if(<字符串|变量> EQUAL <字符串|变量>) # 等于
        if(<字符串|变量> LESS_EQUAL <字符串|变量>) # 小于或等于
        if(<字符串|变量> GREATER_EQUAL <字符串|变量>) # 大于或等于
    - 字符串比较
        if(<字符串|变量> STRLESS <字符串|变量>) # 小于
        if(<字符串|变量> STRGREATER <字符串|变量>) # 大于
        if(<字符串|变量> STREQUAL <字符串|变量>) # 等于
        if(<字符串|变量> STRLESS_EQUAL <字符串|变量>) # 小于或等于
        if(<字符串|变量> STRGREATER_EQUAL <字符串|变量>) # 大于或等于
    - 字符串匹配
        if(<字符串|变量> MATCHES <正则表达式>)
    - 版本号比较
        if(<字符串|变量> VERSION_LESS <字符串|变量>) # 小于
        if(<字符串|变量> VERSION_GREATER <字符串|变量>) # 大于
        if(<字符串|变量> VERSION_EQUAL <字符串|变量>) # 等于
        if(<字符串|变量> VERSION_LESS_EQUAL <字符串|变量>) # 小于或等于
        if(<字符串|变量> VERSION_GREATER_EQUAL <字符串|变量>) # 大于或等于
    - 列表元素判断
        if(<字符串|变量> IN_LIST <列表变量>)
]]
# 版本号格式：主版本号[.次版本号[.补丁版本号[.修订版本号]]]
message(============双参数条件============)

set(a 10)
set(b "abc")
set(list 1;10;100)
if(11 GREATER a)
    message("11 GREATER a为真")
endif()

if(1 LESS 2)
    message("1 LESS 2为真")
endif()

if(b STRLESS "b")
    message("b LESS \"b\"为真")
endif()

if(1.2.3 VERSION_LESS 1.10.1)
    message("1.2.3 LESS 1.10.1为真")
endif()

if(abc MATCHES a..)
    message("abc MATCHES a..为真")
endif()

if(ab MATCHES a..)
else()
    message("ab MATCHES a..为假")
endif()

if(a IN_LIST list)
    message("a IN_LIST list为真")
endif()

#[[
变量展开：在条件语法中，可以直接通过变量名而不是变量引用语法来访问变量的值，并对其进行条件判断。

    - 一般将条件语法中直接访问变量值的这种行为称作变量展开(variable expansion)。它类似于变量引用功能，但仅适用于条件语法中，且与变量引用语法显然不同，需要加以区分。
    - 判断一个可能未被定义的变量是否为真值时，使用变量展开可能更加方便，直接用 if(A) 就可以了。如果使用变量引用的语法 if(${A})，那么当变量 A 未被定义或为空值时，CMake 反而会认为没有向 if 传递任何参数而报错。

]]
message(============变量展开============)

set(A FALSE)
set(B "A")

if(B)
    message("B为真")
endif()

if(${B})
else()
    message("\${B}为假")
endif()

while(NOT ${B})
    message("NOT \${B}为真")
    break()
endwhile()


# 注意：在 CMake 条件语法中，引号参数和括号参数中的变量都不会被展开。
message(============变量展开时机============)
set(A "NOT A")
set(B "A")
if(${B} STREQUAL "A")
else()
    message("\${B} STREQUAL \"A\"为假")
endif()

if("${B}" STREQUAL "A")
    message("\"\${B}\" STREQUAL \"A\"为真")
endif()