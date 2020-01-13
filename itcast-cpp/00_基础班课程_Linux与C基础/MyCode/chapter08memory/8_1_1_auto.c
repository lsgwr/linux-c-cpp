/***********************************************************
 * @Description : 局部变量之auto
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 21:59
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>

void test(){
    auto int b = 10;
}

int main(void) {
    if (1){
        int a = 10;
        printf("%d\n", a);
    }
//    a=10;
    return 0;
}
