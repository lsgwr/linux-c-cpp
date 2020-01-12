/***********************************************************
 * @Description : const修饰的指针变量
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 20:44
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>
#include <string.h>

int main() {
    // const修饰一个变量为只读
    const int a = 10;

    // 指针变量，指针指向的内存，两个不同的概念
    char buf[] = "aklgjdlsgjlkds";

    // 从左往右看，跳过类型，看修饰那个字符
    // 1.如果是*，表明指针指向的内存不能改变
    // 2.如果是指针变量，说明指针的指向不能改变，即指针的值不能修改
    const char *p1 = buf; // 指针指向的内容不能变，即*p = '2'会报错
    p1 = "agdsdsfsgrgr"; //ok:可以修改指针的方向

    char * const p2 = buf; // 修饰变量，指向的方向不能变，内容可以边
    p2[1] = '3';

    // 指针指向不能变，指向的内容也不能变
    const char * const p3 = buf;
    return 0;
}
