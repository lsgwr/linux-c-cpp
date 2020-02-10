/***********************************************************
 * @Description : 字符串的输入和输出
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 13:25
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <stdio.h>

int main() {
    char str[100];

    printf("input string1 : ");
    scanf("%s", str); // 默认用空格分隔
    printf("ouput:%s\n", str);
    return 0;
}
/**
input string1 : sds
sds
ouput:sds
 */
