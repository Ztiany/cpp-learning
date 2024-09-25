#[[
构建说明：
        1. 仅支持 MSCV 编译器；
        2. 下载 Boost 预构建库（当然也可以下载源码自己编译）
                2.1 由于 C++ 标准不保证编译后的应用程序二进制接口(Application Binary Interface，ABI)稳定性，不同版本的
                    编译器编译出的程序无法保证相互引用而不出错。所以，我们必须根据微软 C++ 工具集(Microsoft C++ Toolset)
                    的版本号来决定安装哪个版本的预编译
                2.2 打开 Visual Studio 命令行工具，输出环境变量 VCToolsVersion：
                            > echo %VCToolsVersion%
                                14.29.30133
                    其中，主版本号 14 和次版本号的第一个数字 2 唯一决定其 ABI 稳定性。也就是说，如果 Boost 库是通过 14.2* 版
                    本的工具集构建的，就能被上述 “14.29.30133” 版本的工具集引用。
                2.3 去 Boost 官网下载对应的预构建版本，比如：boost_1_76_0-msvc-14.2-64，这里
                        1_76_0 是 Boost 的版本
                        14.2-64 是 mscv 版本
        3. 安装 boost，然后将 boost 的根目录添加环境变量中。比如安装目录为 “C:\boost_prebuilt”，则可以添加一个 BOOST_ROOT 环境变量来指向这个路径。
]]
cmake_minimum_required(VERSION 3.29)
project(cmake_in_practice_02_build)
set(CMAKE_CXX_STANDARD 20)

# 尝试查找 Boost 的 regex 库（下面这种写法需要设置 BOOST_ROOT 环境变量指向 Boost 的根目录）。
find_package(Boost REQUIRED COMPONENTS regex )  # 根据需要添加其他组件

# 下面变量 Boost_FOUND, Boost_LIBRARIES 等变量是由 find_package(Boost ...) 命令生成的。
# 这个命令会查找指定的 Boost 库，并设置相关的 CMake 变量，以便后续使用。
message("Boost_FOUND: " ${Boost_FOUND})
message("Boost_LIBRARIES: " ${Boost_LIBRARIES})
message("Boost_INCLUDE_DIRS: " ${Boost_INCLUDE_DIRS})

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(cmake_in_practice_02_build main.cpp)
    target_link_libraries(cmake_in_practice_02_build ${Boost_LIBRARIES})
endif()