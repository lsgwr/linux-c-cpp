/***********************************************************
 * @Description : strtok(s, delim)
 * 将字符串分割成一个个片段，返回分割后的首地址.类似split函数
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 16:57
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <stdio.h>
#include <string.h>

int main() {
    char a[100] = "abc*fvcv*ebcy*hghbdfg*casdert";
    char *s = strtok(a, "*");
    while (s != NULL) {
        printf("%s\t", s);
        s = strtok(NULL, "*");
    }
    return 0;
}
/**
abc	fvcv	ebcy	hghbdfg	casdert
 */

