/***********************************************************
 * @Description : 指针变量的定义和使用
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 18:20
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>

int main() {
    int a = 22;
    char b = 100;
    printf("%p, %p\n", &a, &b);

    // int * 代表地是一种数据类型，int*指针类型，p才是变量名
    // 定义了一个指针类型的变量，可以指向一个int类型变量的地址
    int *p;
    // &表示取地址，将a的地址赋值给变量p，p也是一个变量，值是一个内存地址编号
    p = &a;
    // *代表取地址里面的值，所以*p就是a的值
    printf("%d\n", *p);

    char *p1 = &b;
    printf("%c\n", *p1);
}
/**
0x7fffe8092fc4, 0x7fffe8092fc3
22
d
 */
