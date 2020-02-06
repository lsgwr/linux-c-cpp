cmake_minimum_required(VERSION 3.15)
project(STL)

set(CMAKE_CXX_STANDARD 11)

add_executable(STL main.cpp)
# 第1章 STL概述
add_executable(01_01 第01章_STL概述/P3_命名空间.cpp)

# 第2章 模板
add_executable(02_01 第02章_模板/P5_动态数组的模板类.cpp)
add_executable(02_02 第02章_模板/P7_数组求和的函数模板.cpp)
add_executable(02_03 第02章_模板/P8_traits技术举例.cpp)
add_executable(02_04 第02章_模板/P10_traits技术进阶.cpp)
add_executable(02_05 第02章_模板/P12_模板与运算符重载.cpp)

# 第3章 迭代器
add_executable(03_01 第03章_迭代器/P17_为数组和链表编制共同的显示函数.cpp)
add_executable(03_02 第03章_迭代器/P26_STL输入迭代器.cpp)
add_executable(03_03 第03章_迭代器/P28_STL输出迭代器.cpp)

# 第4章 输入输出流
add_executable(04_01 第04章_输入输出流/P31_标准输入输出流给不同变量赋值.cpp)
add_executable(04_02 第04章_输入输出流/P32_标准输入给不同类型变量赋值的不足示例.cpp)
add_executable(04_03 第04章_输入输出流/P33_get和getline函数示例.cpp)
add_executable(04_04 第04章_输入输出流/P34_判断是否是输入地整数.cpp)
add_executable(04_05 第04章_输入输出流/P35_确保输入一个整型数给变量a.cpp)
add_executable(04_06 第04章_输入输出流/P37_读文本文件并显示在屏幕上.cpp)
add_executable(04_07 第04章_输入输出流/P37_把学生信息保存到文件中.cpp)
add_executable(04_08 第04章_输入输出流/P38_write写二进制文件.cpp)
add_executable(04_09 第04章_输入输出流/P38_读取二进制文件.cpp)
add_executable(04_10 第04章_输入输出流/P39_读取文件所有内容.cpp)
add_executable(04_11 第04章_输入输出流/P40_定位输入输出流.cpp)
add_executable(04_12 第04章_输入输出流/P41_解析字符串给不同类型的变量赋值.cpp)
add_executable(04_13 第04章_输入输出流/P42_合并不同类型的数据到字符串.cpp)
add_executable(04_14 第04章_输入输出流/P42_从键盘中读取学生对象并显示.cpp)
add_executable(04_15 第04章_输入输出流/P44_从文本中读取每个学生的各科成绩_方法1.cpp)
add_executable(04_16 第04章_输入输出流/P45_从文本中读取每个学生的各科成绩_方法2.cpp)