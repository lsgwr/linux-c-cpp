/***********************************************************
 * @Description : 指针数组
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 19:40
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>

int main() {
    int *p[3];
    int a = 1, b = 2, c = 3;
    p[0] = &a;
    p[1] = &b;
    p[2] = &c;

    int len = sizeof(p) / sizeof(p[0]);
    for (int i = 0; i < len; ++i) {
        printf("%d\t", *(p[i]));
    }
    printf("\n");
    return 0;
}
