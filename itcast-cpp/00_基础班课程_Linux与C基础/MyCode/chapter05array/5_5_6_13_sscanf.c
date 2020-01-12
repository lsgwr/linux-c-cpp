/***********************************************************
 * @Description : 字符串格式化函数sscanf(str, format)
 * 从str指定的字符串中读取数据，并根据参数format字符串来转换并格式化数据
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 16:43
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <stdio.h>

int main() {
    char src[] = "a=10, b=20";
    int a, b;
    // 从字符串取值赋给整型变量
    sscanf(src, "a=%d, b=%d", &a, &b);
    printf("a:%d, b:%d\n", a, b);
    return 0;
}
/**
a:10, b:20
 */

