#[[
列表变量：列表是用分号隔开的字符串。既然列表也是字符串，那么定义列表变量并不会有什么特别的。

    - 可以利用引号参数直接定义一个包含分号的字符串，这就是一个列表。
    - 其次，set命令还支持指定多个作为变量值的参数，这样引号参数和非引号参数都可以使用。

]]
include(subscript/print_list.cmake)
set(a "a;b;c")
set(b a;b;c)
set(c a b c)
set(d a b c d e f g)
print_list(${a}) # 输出：a | b | c
print_list(${b}) # 输出：a | b | c
print_list(${c}) # 输出：a | b | c
print_list(${d})


#[[
特殊的分号：

    - 列表的每一个元素都是被分号隔开的，但不是每一个分号都用于分隔元素。当分号前面有一个用于转义的反斜杠时，这个分号不会用作分隔符。
    - 另外，如果一个分号前面存在未闭合的方括号时，该分号也不会被当作元素的分隔符。
]]

# 分号的特殊处理是为了兼容 Windows 中的注册表项查询。
get_filename_component(
        SDK_ROOT_PATH
        "[HKEY_LOCAL_MACHINE\\SOFTWARE\\PACKAGE;Install_Dir]"
        ABSOLUTE CACHE)
message("SDK_ROOT_PATH: " ${SDK_ROOT_PATH})

include(subscript/print_list.cmake)
set(a "a;b\;c")
set(b "a[;]b;c")
set(c "a[[[;]]]b;c")
set(d "a[;b;c")
set(e "a[];b")
print_list(${a}) # 输出：a | b;c
print_list(${b}) # 输出：a[;]b | c
print_list(${c}) # 输出：a[[[;]]]b | c
print_list(${d}) # 输出：a[;b;c
print_list(${e}) # 输出：a[] | b