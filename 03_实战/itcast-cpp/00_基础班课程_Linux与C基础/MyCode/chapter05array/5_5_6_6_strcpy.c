/***********************************************************
 * @Description : 字符串处理函数之strcpy(dst, src)
 * 把src所指向的字符串复制到dst所指向的空间中, '\0'也会拷贝过去
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 16:04
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <stdio.h>
#include <string.h>

int main() {
    char dst[20] = "1234567890sdsss";
    char src[] = "hello world";
    strcpy(dst, src);
    printf("%s\n", dst);
    return 0;
}
/**
hello world
 */

