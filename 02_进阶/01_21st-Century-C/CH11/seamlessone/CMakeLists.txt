cmake_minimum_required(VERSION 3.22)
project(seamlessone C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-fms-extensions")
add_executable(seamlessone main.c)
