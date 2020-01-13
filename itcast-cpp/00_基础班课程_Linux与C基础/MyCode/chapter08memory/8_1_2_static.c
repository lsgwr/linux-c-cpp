/***********************************************************
 * @Description : 局部变量之static
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 22:03
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>

void func1() {
    int i = 0;
    i++;
    printf("i = %d\n", i);
}

void func2() {
    // 静态局部变量，没有赋值，系统赋值为0，而且只会初始化一次
    static int a;
    a++;
    printf("a = %d\n", a);
}

int main(void) {
    func1();
    func1();
    func2();
    func2();
    return 0;
}
/**
i = 1
i = 1
a = 1
a = 2
 */
