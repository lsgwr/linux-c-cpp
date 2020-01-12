/***********************************************************
 * @Description : 字符指针作为函数参数
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 20:32
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>
#include <string.h>

/**
 * 字符串函数
 * @param dst 目标字符串首地址
 * @param src 源字符串首地址
 */
void myStrcat(char *dst, char *src) {
    int len1 = strlen(dst);
    int len2 = strlen(src);
    for (int i = 0; i < len2; ++i) {
        dst[len1 + i] = src[i];
    }
}

int main() {
    char dst[100] = "hello mike";
    char src[] = "123456";

    myStrcat(dst, src);
    printf("dst = %s\n", dst);
    return 0;
}
