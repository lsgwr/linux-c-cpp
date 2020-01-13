/***********************************************************
 * @Description : 值传递
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/14 00:18
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>
#include <stdlib.h>

int *fun(int *tmp) {
    // tmp重新赋值了，所以不会修改p
    tmp = (int *) malloc(sizeof(int));
    *tmp = 100;
}

int main(void) {
    int *p = NULL;
    fun(p); // 值传递，形参改变不会影响实参
    printf("*p=%d\n", *p); // err,操作了空指针指向的内存
    return 0;
}
/**
 * *p=100
 */
