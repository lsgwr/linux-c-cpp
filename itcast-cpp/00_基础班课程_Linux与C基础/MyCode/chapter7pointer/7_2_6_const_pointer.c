/***********************************************************
 * @Description : const指针
 * 1.const修饰数据类型： 指针指向的内存内容不能修改，但指针指向可以修改
 * 2.const修改变量名  ： 指针指向不能修改，但指针指向的内存内容可以修改
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 18:55
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>

int main() {
    int a = 100, b = 200;
    // const修饰数据内容：指针指向内容不能改，指针指向可以改
    const int *p1 = &a;
    p1 = &b;
    // const修饰变量名：指针指向的内容可以改，但是指针指向不能改
    int * const p2 = &a;
    *p2 = 222;
    printf("%d\a", a);
    return 0;
}
