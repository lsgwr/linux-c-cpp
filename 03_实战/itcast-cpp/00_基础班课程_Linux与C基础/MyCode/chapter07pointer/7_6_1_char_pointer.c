/***********************************************************
 * @Description : 字符指针
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 20:28
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>

int main() {

    char str[] = "hello world";
    char *p = str;
    *p = 'm'; // 数组首元素改成m
    printf("%s\n", str);
    p++;
    *p = 'i'; // 数组第二个元素改成i
    printf("%s\n", str);
    printf("%s\n", p);

    p = "mike jiang"; // p重新指针一个新的字符串
    printf("%s\n", p);

    char *q = "test";
    printf("%s\n", q);
    return 0;
}
