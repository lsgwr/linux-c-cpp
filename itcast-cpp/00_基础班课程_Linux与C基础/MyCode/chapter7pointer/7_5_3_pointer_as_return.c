/***********************************************************
 * @Description : 指针作为函数的返回值
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 20:05
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>
int a = 10;
int *getA(){
    return &a;
}

int main() {
    // 通过函数返回值修改a的值
    *(getA()) = 111;
    printf("a = %d\n", a);
    return 0;
}
