/***********************************************************
 * @Description : 指针加法
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 19:11
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>

int main() {
    int a;
    int *p1 = &a;
    printf("p1 = %d\n", p1);
    p1 += 2; // 移动了2个int，即8位
    printf("p1 = %d\n", p1);

    char b = 0;
    char *p2 = &b;
    printf("p2 = %d\n", p2);
    p2 += 2; // 移动两个char及2位
    printf("p2 = %d\n", p2);

    int c[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int len = sizeof(c) / sizeof(c[0]);
    int *p = c;
    for (int i = 0; i < len; ++i) {
        printf("%d\t", *p);
        p++;
    }
    printf("\n");
    return 0;
}
