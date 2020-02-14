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
add_executable(06_03 第06章_类和对象/P137_自由存储对象.cpp)
add_executable(06_05 第06章_类和对象/P142_引用静态数据成员.cpp)
add_executable(06_06 第06章_类和对象/P143_成员函数.cpp)
add_executable(06_07 第06章_类和对象/P146_常成员函数.cpp)
add_executable(06_08 第06章_类和对象/P147_常数据成员.cpp)
add_executable(06_09 第06章_类和对象/P149_将普通函数声明为友元函数.cpp)
add_executable(06_10 第06章_类和对象/P150_友元成员函数.cpp)
add_executable(06_11 第06章_类和对象/P151_友元类.cpp)

# 第07章 继承和派生
add_executable(07_01 第07章_继承和派生/P167_派生类的定义和组成.cpp)
add_executable(07_06 第07章_继承和派生/P173_派生类的构造函数.cpp)
add_executable(07_07 第07章_继承和派生/P175_调用成员对象的构造函数.cpp)
add_executable(07_08 第07章_继承和派生/P177_派生类和成员对象构造函数.cpp)
add_executable(07_09 第07章_继承和派生/P179_派生类的析构函数.cpp)
add_executable(07_virtual_test1 第07章_继承和派生/P181_二义性测试.cpp)
add_executable(07_virtual_test2 第07章_继承和派生/P182_二义性测试2.cpp)
add_executable(07_virtual_test3 第07章_继承和派生/P183_虚基类解决二义性的问题.cpp)
add_executable(07_10 第07章_继承和派生/P185_虚基类构造函数_析构函数_成员变量.cpp)
add_executable(07_11 第07章_继承和派生/P188_子类型关系.cpp)
add_executable(07_12 第07章_继承和派生/P191_继承中的同名函数.cpp)
add_executable(07_12_2 第07章_继承和派生/P191_继承中的同名函数2.cpp)
add_executable(07_13 第07章_继承和派生/P194_派生类对象赋给基类病调用析构函数.cpp)
add_executable(07_13_2 第07章_继承和派生/P194_派生类对象赋给基类病调用析构函数2.cpp)
add_executable(07_14 第07章_继承和派生/P196_纯虚函数示意.cpp)
add_executable(07_15 第07章_继承和派生/P197_抽象类中虚函数的重写.cpp)

# 第08章 运算符重载
add_executable(08_01 第08章_运算符重载/P210_复数运算.cpp)

# 第09章 模板函数实例化
add_executable(09_01 第09章_模板/P230_模板函数实例化.cpp)
add_executable(09_02 第09章_模板/P234_类模板的定义和实例化.cpp)

# 第10章 流
add_executable(10_01 第10章_流/P247_输入输出控制.cpp)
