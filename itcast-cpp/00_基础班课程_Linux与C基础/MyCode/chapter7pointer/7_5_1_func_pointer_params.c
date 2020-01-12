/***********************************************************
 * @Description : 函数形参改变实参的值
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 19:50
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>

/**
 * 变量传参，无法改变实参的值
 * @param x
 * @param y
 */
void swap1(int x, int y) {
    int tmp = x;
    x = y;
    y = tmp;
}

/**
 * 指针传参，可以改变实参
 * @param x 指针
 * @param y 指针
 */
void swap2(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int main() {
    int a = 3, b = 5;
    swap1(a, b);
    printf("a = %d, b = %d\n", a, b);

    a = 3, b = 5;
    swap2(&a, &b);
    printf("a = %d, b = %d\n", a, b);
    return 0;
}
