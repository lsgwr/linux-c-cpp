cmake_minimum_required(VERSION 2.8.4)
project(MyCode C)

set(CMAKE_C_STANDARD 99)

add_executable(MyCode main.c)
add_executable(5_2_1 chapter05array/5_2_1_one_dim_array.c)
add_executable(5_2_2 chapter05array/5_2_2_one_dim_array_init.c)
add_executable(5_2_3 chapter05array/5_2_3_one_dim_array_name.c)
add_executable(5_2_4 chapter05array/5_2_4_max_of_one_dim_array.c)
add_executable(5_2_4_2 chapter05array/5_2_4_reverse_one_dim_array.c)
add_executable(5_2_4_3 chapter05array/5_2_4_bubble_sort_one_dim_array.c)