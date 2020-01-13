/***********************************************************
 * @Description : 返回栈区地址
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/14 00:11
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>

int a = 10;

int *fun() {
    return &a; // 函数调用完毕,a释放
}

int main(void) {
    int *p = NULL;
    p = fun();
    *p = 100; // 操作野指针指向的内存,error
    return 0;
}
