cmake_minimum_required(VERSION 3.15)
project(STL)

set(CMAKE_CXX_STANDARD 11)

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

# 第5章 字符串
add_executable(05_01 第05章_字符串/P47_字符串的基本创建方式.cpp)
add_executable(05_02 第05章_字符串/P48_迭代器创建方式.cpp)
add_executable(05_03 第05章_字符串/P48_字符串插入.cpp)
add_executable(05_04 第05章_字符串/P49_替换操作.cpp)
add_executable(05_05 第05章_字符串/P51_字符串查询函数基本用法.cpp)
add_executable(05_06 第05章_字符串/P52_在字符串中删除字符.cpp)
add_executable(05_07 第05章_字符串/P53_字符串比较函数.cpp)
add_executable(05_08 第05章_字符串/P53_整型数据和字符串相互转化.cpp)
add_executable(05_09_1 第05章_字符串/P54_利用STL拆分字符串1.cpp)
add_executable(05_09_2 第05章_字符串/P55_利用STL拆分字符串2.cpp)
add_executable(05_10 第05章_字符串/P56_STL实现trim功能.cpp)
add_executable(05_11 第05章_字符串/P57_字符串工具类.cpp)

# 第6章 函数对象
add_executable(06_01 第06章_函数对象/P61_求整型向量各元素之和.cpp)
add_executable(06_02_01 第06章_函数对象/P62_1_利用一元函数求向量各元素之和.cpp)
add_executable(06_02_02 第06章_函数对象/P62_2_利用一元函数求向量各元素之和.cpp)
add_executable(06_03 第06章_函数对象/P64_二元函数.cpp)
add_executable(06_04 第06章_函数对象/P67_算术类基本函数使用.cpp)
add_executable(06_05 第06章_函数对象/P68_非常规数据类型基本函数的使用.cpp)
add_executable(06_06 第06章_函数对象/P70_关系运算符基本函数使用.cpp)
add_executable(06_07 第06章_函数对象/P71_利用二元函数比较两个复数是否相等.cpp)
add_executable(06_08 第06章_函数对象/P72_逻辑运算符函数对象使用.cpp)
add_executable(06_09 第06章_函数对象/P73_绑定和取反适配器基本用法.cpp)
add_executable(06_10 第06章_函数对象/P74_成员函数适配器基本方法.cpp)
add_executable(06_11 第06章_函数对象/P76_普通函数适配器使用.cpp)
add_executable(06_12 第06章_函数对象/P77_综合案例_求圆和长方形的面积.cpp)
add_executable(06_13 第06章_函数对象/P78_学生成绩输出.cpp)