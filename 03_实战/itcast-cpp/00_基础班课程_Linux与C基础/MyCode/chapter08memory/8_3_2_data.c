/***********************************************************
 * @Description : 返回data区地址
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/14 00:14
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>


int *fun() {
    static int a = 10;
    return &a; // 函数调用完毕,a释放
}

int main(void) {
    int *p = NULL;
    p = fun();
    *p = 100; //
    printf("*p=%d\n", *p);
    return 0;
}
/**
 * *p=100
 */
