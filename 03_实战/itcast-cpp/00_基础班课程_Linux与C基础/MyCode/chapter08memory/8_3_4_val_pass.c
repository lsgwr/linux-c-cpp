/***********************************************************
 * @Description : 值传递
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/14 00:22
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>
#include <stdlib.h>

int *fun(int *tmp) {
    *tmp = 100;
}

int main(void) {
    int *p = NULL;
    p = (int *)malloc(sizeof(int));
    fun(p); // 值传递，形参改变不会影响实参
    printf("*p=%d\n", *p); // err,操作了空指针指向的内存
    return 0;
}
/**
 * *p=100
 */
