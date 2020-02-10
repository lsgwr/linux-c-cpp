/***********************************************************
 * @Description : ato类的函数，把字符串转换成其他类型的数据
 * atoi() 转成整型
 * atof() 转成浮点型
 * atol() 转成long型
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 17:04
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

int main() {
    char str1[] = "-10";
    int num1 = atoi(str1);
    printf("num1 = %d\n", num1);

    char str2[] = "0.123";
    float num2 = atof(str2);
    printf("num2 = %f\n", num2);
    return 0;
}
/**
num1 = -10
num2 = 0.123000
 */

