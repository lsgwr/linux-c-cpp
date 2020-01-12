/***********************************************************
 * @Description : 万能指针void *
 * 最长用的地方其实是使用struct模拟面向对象时对函数进行强制转换
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 18:46
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>

int main() {
    void *p = NULL;

    int a = 10;
    p = (void *)&a; // 指向变量时，最好转换为void*

    // 使用指针变量指向的内存时，要把void指针再转换回去
    *((int *)p) = 11;
    printf("a = %d\n", a);
    return 0;
}
