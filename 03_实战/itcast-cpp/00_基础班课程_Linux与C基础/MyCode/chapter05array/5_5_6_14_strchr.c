/***********************************************************
 * @Description : strchr(s, c)
 * 在字符串s中查找字母c出现的位置，返回第一次c出现的地址
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 16:50
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <stdio.h>
#include <string.h>

int main() {
    char src[] = "ddda123abcd";
    char *p = strchr(src, 'a');
    printf("%s\n", p); // 取出发现位置往后的字符串
    return 0;
}
/**
a:10, b:20
 */

