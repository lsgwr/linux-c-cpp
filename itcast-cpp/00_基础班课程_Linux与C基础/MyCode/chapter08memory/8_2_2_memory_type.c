/***********************************************************
 * @Description : 存储类型
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/13 07:46
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>
#include <stdlib.h>

int e;
static int f;
int g = 10;
static int h = 10;

int main(void) {
    int a;
    int b = 10;
    static int c;
    static int d = 10;
    char *i = "test";
    char *k = NULL;

    printf("&a\t %p\t // 局部未初始化变量\n", &a);
    printf("&b\t %p\t // 局部初始化变量\n", &b);

    printf("&c\t%p\t // 静态局部未初始化变量\n", &c);
    printf("&d\t%p\t // 静态局部初始化变量\n", &d);

    printf("&e\t %p\t // 全局未初始化变量\n", &e);
    printf("&f\t%p\t // 全局静态未初始化变量\n", &f);

    printf("&g\t%p\t // 全局初始化变量\n", &g);
    printf("&h\t%p\t // 全局静态初始化变量\n", &h);

    printf("i\t%p\\t //只读数据(文字常量区)\n", i);
    k = (char *) malloc(10);
    printf("k\t%p\t // 动态分配的内存\n", k);
    return 0;
}
