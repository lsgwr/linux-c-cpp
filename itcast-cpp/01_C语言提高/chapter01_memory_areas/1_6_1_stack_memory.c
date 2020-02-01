/***********************************************************
 * @Description : 
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/19 7:53
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>

int main(void){
    int a;
    int b;
    char buf[4];
    printf("&a:%p\n", &a);
    printf("&b:%p\n", &b);

    printf("buf的地址：%p\n", &buf[0]);
    printf("buf+1的地址：%p\n", &buf[1]);
    return 0;
}
