cmake_minimum_required(VERSION 3.8)
project(LinuxC)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c chapter3function/list.c chapter3function/list.h chapter11process/myprocess.c chapter11process/myprocess.h common/common.c common/common.h)
add_executable(LinuxC ${SOURCE_FILES})