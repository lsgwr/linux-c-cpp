/***********************************************************
 * @Description : 字符串处理函数之fgets(char *s, int size, FILE *stream)
 * 从指定的文件中读入字符到s中，直到出现换行字符、读到文件结尾或是已读了size-1个字符为止，
 * 最后函数会自动加上字符串结束字符'\0'作为字符串结束
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 13:53
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <stdio.h>

int main() {
    char str[100];
    printf("请输入str:");
    fgets(str, sizeof(str), stdin);
    printf("str = %s\n", str);
    return 0;
}
/**
请输入str:sdsdsfs
sdsdsfs
str = sdsdsfs
 */
