/***********************************************************
 * @Description : 字符串处理函数之gets()
 * 从标准输入读入字符，并保存到s指定的内存空间，直到出现换行符或读到文件结尾
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 13:47
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <stdio.h>

int main() {
    char str[100];
    printf("请输入str:");
    gets(str);
    printf("str = %s\n", str);
    return 0;
}
/**
请输入str:sdsdsfs
sdsdsfs
str = sdsdsfs
 */
