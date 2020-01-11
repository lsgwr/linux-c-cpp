/***********************************************************
* @Description : 一位数组的定义和使用
* @author      : 梁山广(Liang Shan Guang)
* @date        : 2020/1/11 21:17
* @email       : liangshanguang2@gmail.com
***********************************************************/
#include <stdio.h>

int main() {
    int a[10];
    for (int i = 0; i < 10; ++i) {
        a[i] = i;
    }
    for (int i = 0; i < 10; ++i) {
        printf("%d\t", a[i]);
    }
    printf("\n");
    return 0;
}
