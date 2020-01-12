/***********************************************************
 * @Description : 指针变量的大小，字节数
 * sizeof(指针变量)结果是指针的大小，32位平台是4，64位平台是8
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 18:38
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>

int main() {
    int *p1;
    int **p2;
    char *p3;
    char **p4;

    printf("sizeof(p1) = %lu\n", sizeof(p1));
    printf("sizeof(p2) = %lu\n", sizeof(p2));
    printf("sizeof(p3) = %lu\n", sizeof(p3));
    printf("sizeof(p4) = %lu\n", sizeof(p4));
}
/**
 * 8
 * 8
 * 8
 * 8
 */
