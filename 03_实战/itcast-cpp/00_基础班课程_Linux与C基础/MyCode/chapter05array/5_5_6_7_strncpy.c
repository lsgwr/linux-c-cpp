/***********************************************************
 * @Description : 字符串处理函数之strncpy(dst, src, size)
 * 把src指向字符串的前n个字符复制到dst所指向的空间中，是否拷贝结束符看指定的长度是否包含\0
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 16:09
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <stdio.h>
#include <string.h>

int main() {
    char dst[20];
    char src[] = "hello world";
    strncpy(dst, src, 5);
    printf("%s\n", dst); // 没有结束符会乱码

    dst[5] = '\0';
    printf("%s\n", dst); // 手动加了结束符后输出就不乱码了
    return 0;
}
/**
hello
hello
 */

