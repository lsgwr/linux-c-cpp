/***********************************************************
 * @Description : 字符串处理函数之strlen
 * 计算指定字符串的长度，不包含字符串结束符 '\0'
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 16:02
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "abcdefg";
    int n = strlen(str);
    printf("字符串str的长度为n=%d\n", n);
    return 0;
}
/**
字符串str的长度为n=7
 */

