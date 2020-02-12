cmake_minimum_required(VERSION 3.10)
project(NCRE2CPP)

set(CMAKE_CXX_STANDARD 11)

# 第04章 数组、指针和引用
add_executable(04_09 第04章_数组_指针_引用/P87_引用与变量的关系.cpp)

# 第05章 函数
add_executable(05_02 第05章_函數/P98_swap.cpp)
add_executable(05_11 第05章_函數/P108_形参默认值.cpp)

# 第06章 类和对象
add_executable(06_01 第06章_类和对象/P129_对象的成员.cpp)
add_executable(06_02 第06章_类和对象/P134_构造函数与析构函数.cpp)