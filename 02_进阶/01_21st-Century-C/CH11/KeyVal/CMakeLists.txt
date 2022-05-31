cmake_minimum_required(VERSION 3.22)
project(KeyVal C)

set(CMAKE_C_STANDARD 11)

add_executable(KeyVal main.c keyval.c keyval.h dict.c dict.h)
