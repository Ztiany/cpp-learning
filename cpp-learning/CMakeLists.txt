cmake_minimum_required(VERSION 3.16)
project(cpp-learning)

# 指定 C 标准
set(CMAKE_CXX_STANDARD 17)

# 禁止编译器优化(测试对象移动)
#add_compile_options(-fno-elide-constructors)

# Put the libaries and binaries that get built into directories at the
# top of the build tree rather than in hard-to-find leaf directories.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# 包含项目目录下的所有的头文件
include_directories(${PROJECT_SOURCE_DIR})

# check epoll and add config.h for the macro compilation
include(CheckSymbolExists)
check_symbol_exists(epoll_create "sys/epoll.h" EPOLL_EXISTS)
if (EPOLL_EXISTS)
    MESSAGE("epoll is available")
    # Linux下设置为 epoll
    set(EPOLL_ENABLE 1 CACHE INTERNAL "enable epoll")
    # Linux下设置为 poll【测试用】
    # set(EPOLL_ENABLE "" CACHE INTERNAL "not enable epoll")
else ()
    MESSAGE("epoll is not available")
    set(EPOLL_ENABLE "" CACHE INTERNAL "not enable epoll")
endif ()

if (EPOLL_ENABLE)
    MESSAGE("epoll is enabled")
endif ()

# 配置生成头文件
#  CMAKE_CURRENT_BINARY_DIR 指的是工程编译结果存放的目标目录
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/include/config.h)
# 包含生成的头文件
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)

# 添加子模块
add_subdirectory(foundation)
add_subdirectory(function)
add_subdirectory(exception)
add_subdirectory(io)
add_subdirectory(ipc)
add_subdirectory(oop)
add_subdirectory(template)
add_subdirectory(threading)
add_subdirectory(smart-pointer)
add_subdirectory(dynamic-memory)
add_subdirectory(design-pattern)
add_subdirectory(interact-with-c)
add_subdirectory(geektime-modern-cpp)

add_subdirectory(mmkv-simulator)
