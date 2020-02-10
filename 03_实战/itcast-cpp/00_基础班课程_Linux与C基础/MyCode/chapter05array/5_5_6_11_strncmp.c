/***********************************************************
 * @Description : 字符串比较函数strncmp(str1, str2, n)
 * 比较str1和str2前n个字符的的大小，比较地是字符ASCII码的大小
 * str1 > str2 返回值大于0
 * str1 < str2 返回值小于0
 * str1 = str2 返回值等于0
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 16:33
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <stdio.h>
#include <string.h>

int main() {
    char str1[] = "hello";
    char str2[] = "hell";

    printf("返回值：%d\n", strncmp(str1, str2, 5));
    printf("返回值：%d\n", strncmp(str1, str2, 4));
    return 0;
}
/**
返回值：111
返回值：0
 */

