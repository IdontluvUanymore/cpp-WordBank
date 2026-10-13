#声明cmake的最低版本要求
cmake_minimum_required(VERSION 3.10)

#给项目命名
project(WordBank LANGUAGES CXX)

#设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#告诉编译器强制按UTF-8读
add_compile_options(/utf-8)

#生成可执行文件
add_executable(word_bank main.cpp)