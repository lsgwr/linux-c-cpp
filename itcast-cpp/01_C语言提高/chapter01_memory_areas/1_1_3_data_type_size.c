/***********************************************************
 * @Description : 数据类型的大小
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/16 7:47
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>

int main(void) {
    int a = 10; // 告诉编译器，分配四个字节的内存
    int b[10]; // 告诉编译器，分配4*10个字节的内存
    printf("b:%p\n", b); // b代表数组首元素的地址
    printf("b+1:%p\n", b+1);
    printf("&b:%p\n", &b); // &b代表整体数组的地址
    printf("&b+1:%p\n", &b + 1);
}

