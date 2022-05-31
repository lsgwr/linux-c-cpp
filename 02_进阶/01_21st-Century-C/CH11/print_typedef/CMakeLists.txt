cmake_minimum_required(VERSION 3.22)
project(print_typedef C)

set(CMAKE_C_STANDARD 11)

add_executable(print_typedef main.c print_typedef.c print_typedef.h)
