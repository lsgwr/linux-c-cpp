/***********************************************************
 * @Description : 内存操作函数之memcmp(s1, s2, n)
 * 比较s1和s2所指向内存区域的前n个字节
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/13 23:52
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>
#include <string.h>

int main(void) {
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int b[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int flag = memcmp(a, b, sizeof(a));
    printf("flag = %d\n", flag);
    return 0;
}
/**
 * 0
 */
