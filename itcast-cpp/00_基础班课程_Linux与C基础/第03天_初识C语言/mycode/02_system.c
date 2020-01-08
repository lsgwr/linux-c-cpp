/***********************************************************
 * @Description : system函数：用于执行另一条命令
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/8 23:12
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("hello");
    system("ls");
    return 0;
}
/**
 * 输出如下
01_hello   CMakeCache.txt  cmake_install.cmake	mycode
02_system  CMakeFiles	   Makefile		mycode.cbp
hello
 */
