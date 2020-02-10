/***********************************************************
 * @Description : 指针减法
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 19:18
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>

int main() {
    int a;
    int *p1 = &a;
    printf("p1 = %d\n", p1);
    p1 -= 2; // 移动了2个int，即8位
    printf("p1 = %d\n", p1);

    char b = 0;
    char *p2 = &b;
    printf("p2 = %d\n", p2);
    p2 -= 2; // 移动两个char及2位
    printf("p2 = %d\n", p2);

    int c[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int len = sizeof(c) / sizeof(c[0]);
    int *p = &c[len - 1];
    for (int i = len - 1; i >= 0; i--) {
        printf("%d\t", *p);
        p--;
    }
    printf("\n");

    int *p3 = &c[4];
    int *p4 = &c[5];
    printf("p3 = %p, p4 = %p\n", p3, p4);
    // 差几个整型
    int n1 = p4 - p3;
    // 差几位
    int n2 = (int) p4 - (int) p3;
    printf("n1 = %d, n2 = %d\n", n1, n2);
    return 0;
}
/**
p1 = -821730348
p1 = -821730356
p2 = -821730349
p2 = -821730351
9	8	7	6	5	4	3	2	1
p3 = 0x7fffcf056420, p4 = 0x7fffcf056424
n1 = 1, n2 = 4
 */
