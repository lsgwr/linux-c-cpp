/***********************************************************
 * @Description : 内存操作函数之memset(void *s, int c, size_t n)
 * 将s的内存区域的前n个字节以参数c填入
 * s:需要操作内存s的首地址
 * c:填充的字符，c虽然为int，但是必须为unsigned char，范围为0~255
 * n:指定需要设置的大小
 * 返回值：s的首地址
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/13 07:59
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
