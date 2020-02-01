cmake_minimum_required(VERSION 3.10)
project(MyCode C)

set(CMAKE_C_STANDARD 99)

# 第1章 内存四区
add_executable(1_1_2 chapter01_memory_areas/1_1_2_data_type_nature.c)
add_executable(1_1_3 chapter01_memory_areas/1_1_3_data_type_size.c)
add_executable(1_1_4 chapter01_memory_areas/1_1_4_typedef.c)
add_executable(1_3_1 chapter01_memory_areas/1_3_1_stack_heap.c)
add_executable(1_3_2 chapter01_memory_areas/1_3_2_global.c)
add_executable(1_6_1 chapter01_memory_areas/1_6_1_stack_memory.c)
