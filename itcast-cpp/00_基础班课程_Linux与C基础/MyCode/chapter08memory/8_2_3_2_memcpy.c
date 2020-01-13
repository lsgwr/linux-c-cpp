/***********************************************************
 * @Description : 内存操作函数之memcpy(dst, src, n)
 * 拷贝src所指的内存内容的前n个字节到dst所指的内存地址上
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/13 08：06
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>
#include <string.h>

int main(void) {
    int a[10];
    memset(a, 0, sizeof(a));
    memset(a, 97, sizeof(a)); // 97是ASCII码，即a
    for (int i = 0; i < 10; ++i) {
        printf("%c\t", a[i]);
    }
    return 0;
}
