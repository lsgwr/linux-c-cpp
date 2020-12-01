cmake_minimum_required(VERSION 3.16)
project(AlgoDesign)

set(CMAKE_CXX_STANDARD 11)

add_executable(main main.cpp)

file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
foreach(file ${files})
    get_filename_component(name ${file} NAME)
    add_executable(${name} ${file})
endforeach()