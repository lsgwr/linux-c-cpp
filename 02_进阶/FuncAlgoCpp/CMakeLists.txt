cmake_minimum_required(VERSION 3.16)
project(FuncAlgoCpp)

set(CMAKE_CXX_STANDARD 11)

# 第1章 基础数据结构
add_executable(01_01 Chapter01Basic/Section01SeqList/SeqList.cpp)
add_executable(01_02 Chapter01Basic/Section02LinkList/LinkList.cpp)

add_executable(FuncAlgoCpp main.cpp)