cmake_minimum_required(VERSION 3.10)

# 获取当前项目目录名，存储到 ProjectId
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# 替换掉下划线
string(REPLACE " " "_" ProjectId ${ProjectId})

# 定义一个项目
project(${ProjectId})
message(ProjectId =  ${ProjectId})

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)

# 添加编译目标为可执行文件
add_executable(Main main.cpp)