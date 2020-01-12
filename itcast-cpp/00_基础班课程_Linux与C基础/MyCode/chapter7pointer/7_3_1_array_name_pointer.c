/***********************************************************
 * @Description : 指针操作数组元素
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 19:06
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>

int main() {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int len = sizeof(a) / sizeof(a[0]);
    for (int i = 0; i < len; ++i) {
        printf("%d\t", *(a + i));
    }
    printf("\n");

    // 定义一个指针变量保存a的地址
    int *p = a;
    for (int i = 0; i < len; ++i) {
        p[i] = 2 * i;
    }

    for (int i = 0; i < len; ++i) {
        printf("%d\t", *(p+i));
    }
    return 0;
}
/**
 */
