/***********************************************************
 * @Description : 多级指针
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 19:45
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>

int main() {
    int a = 10;
    int *p = &a; // 一级指针
    *p = 100;
    printf("%d\n", a);
    int **q = &p;

    **q = 200;
    printf("%d\n", a);
    return 0;
}
