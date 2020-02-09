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

# 第7章 通用容器
## vector
add_executable(07_01 第07章_通用容器/vector/P84_向量初始化方法举例.cpp)
add_executable(07_02 第07章_通用容器/vector/P86_基本变量增加及获得元素.cpp)
add_executable(07_03 第07章_通用容器/vector/P87_类对象的添加及获得元素.cpp)
add_executable(07_04 第07章_通用容器/vector/P90_修改元素示例.cpp)
add_executable(07_05 第07章_通用容器/vector/P91_删除元素.cpp)
add_executable(07_06 第07章_通用容器/vector/P93_vector综合示例对象查询.cpp)
add_executable(07_07 第07章_通用容器/vector/P95_vector综合案例之书籍出版.cpp)
## deque
add_executable(07_08 第07章_通用容器/deque/P98_基础操作.cpp)
add_executable(07_09 第07章_通用容器/deque/P99_deque和vector内存分配比较示例.cpp)
add_executable(07_10 第07章_通用容器/deque/P100_用deque实现一个先进先出的队列.cpp)
## list
add_executable(07_11 第07章_通用容器/list/P104_基本操作.cpp)
add_executable(07_12 第07章_通用容器/list/P105_list遍历示例.cpp)
add_executable(07_13_1 第07章_通用容器/list/P105_splice.cpp)
add_executable(07_13_2 第07章_通用容器/list/P106_merge.cpp)
## stack和queue
add_executable(07_16 第07章_通用容器/stack_queue/P115_stack的基本操作.cpp)
add_executable(07_17 第07章_通用容器/stack_queue/P117_queue的基本操作.cpp)
add_executable(07_18 第07章_通用容器/stack_queue/P118_实现一个大小固定的堆栈类.cpp)
## priority queue
add_executable(07_20_1 第07章_通用容器/priority_queue/P122_1_整型序列进出优先队列_降序.cpp)
add_executable(07_20_2 第07章_通用容器/priority_queue/P122_2_整型序列进出优先队列_升序.cpp)
add_executable(07_21 第07章_通用容器/priority_queue/P123_优先队列给学生成绩排序.cpp)
add_executable(07_22 第07章_通用容器/priority_queue/P124_固定大小的优先队列.cpp)
## bitset
add_executable(07_23 第07章_通用容器/biset/P127_定义位变量.cpp)
add_executable(07_24 第07章_通用容器/biset/P128_位操作函数示例.cpp)
add_executable(07_25 第07章_通用容器/biset/P129_8位二进制数高4位不变低4位取反.cpp)
## set and multiset
add_executable(07_28 第07章_通用容器/set/P134_3种形成集合的方法.cpp)
add_executable(07_29 第07章_通用容器/set/P135_集合的常用方法.cpp)
add_executable(07_30 第07章_通用容器/set/P137_求集合的交并差.cpp)
## map
add_executable(07_31 第07章_通用容器/map/P141_两种常用地形成映射的方法.cpp)
add_executable(07_32 第07章_通用容器/map/P143_单映射map中的operator中括号用法.cpp)

# 第8章 非变异算法(不改变原始数据结构)
## 循环
add_executable(08_01 第08章_非变异算法/01_循环/P154_for_each.cpp)
add_executable(08_02 第08章_非变异算法/01_循环/P155_求vector的最大最小以及和.cpp)
## 查询
add_executable(08_03 第08章_非变异算法/02_查询/P161_7个查询函数的简单应用.cpp)
add_executable(08_04 第08章_非变异算法/02_查询/P162_根据学号查询学生信息.cpp)
## 计数
add_executable(08_06 第08章_非变异算法/03_计数/P170_求数组中有多少个0.cpp)
add_executable(08_07 第08章_非变异算法/03_计数/P170_查询多少学生成绩为80分.cpp)
add_executable(08_08 第08章_非变异算法/03_计数/P171_查询多少学生成绩高于80分.cpp)
## 比较
add_executable(08_09 第08章_非变异算法/04_比较/P173_比较两个整形数组是否相等.cpp)
add_executable(08_10 第08章_非变异算法/04_比较/P174_寻找两个整型数组不相等时的元素值.cpp)
add_executable(08_11 第08章_非变异算法/04_比较/P174_查询第一对成绩不相等学生的信息.cpp)

# 第9章 变异算法
## 复制
add_executable(09_01 第09章_变异算法/01_复制/P179_copy示例.cpp)
## 交换
add_executable(09_02 第09章_变异算法/02_交换/P181_swap举例.cpp)
## 变换
add_executable(09_03 第09章_变异算法/03_变换/P183_transform示例.cpp)
add_executable(09_04 第09章_变异算法/03_变换/P185_字符串加密后输出.cpp)
## 替换
add_executable(09_05 第09章_变异算法/04_替换/P188_4个replace函数示例.cpp)
add_executable(09_06 第09章_变异算法/04_替换/P189_replace的易错案例.cpp)
add_executable(09_07 第09章_变异算法/05_填充/P191_fill函数简单示例.cpp)
## 生成
add_executable(09_09 第09章_变异算法/06_生成/P194_生成随机数.cpp)
## 删除
add_executable(09_11 第09章_变异算法/07_删除/P199_remove简单示例.cpp)
add_executable(09_12 第09章_变异算法/07_删除/P201_remove_copy示例.cpp)
add_executable(09_13 第09章_变异算法/07_删除/P202_学生信息筛选.cpp)
## 唯一
add_executable(09_14 第09章_变异算法/08_唯一/P205_unique示例.cpp)
add_executable(09_15 第09章_变异算法/08_唯一/P206_单词统计.cpp)
## 反转
add_executable(09_16 第09章_变异算法/09_反转/P208_reverse.cpp)
## 移位
add_executable(09_17 第09章_变异算法/10_环移/P210_循环显示.cpp)
add_executable(09_18 第09章_变异算法/10_环移/P211_list中环移函数用法.cpp)
## 随机
add_executable(09_19 第09章_变异算法/11_随机/P212_随机函数示例.cpp)
add_executable(09_20 第09章_变异算法/11_随机/P213_自定义随机函数生成器.cpp)
## 划分
add_executable(09_21 第09章_变异算法/12_划分/P216_划分函数示例.cpp)
add_executable(09_23 第09章_变异算法/12_划分/P218_list中按照小于4进行划分.cpp)