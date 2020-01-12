/***********************************************************
 * @Description : 字符串处理函数之strcat(dst, src)
 * 将字符串src连接到dst的尾部，'\0'也会被追加过去
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 16:09
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <stdio.h>
#include <string.h>

int main() {
    char dst[20] = "123";
    char src[] = "hello world";
    strcat(dst, src);
    printf("dst=%s\n", dst);
    return 0;
}
/**
dst=123hello world
 */

