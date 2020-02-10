#include <stdio.h>		
#include "caculate.h"  //包含静态库的头文件

int main(void)
{
    double a = 10.5;
    double b = 20.6;
    double ret = 0;

    ret = add(a, b); //加
    printf("add: ret = %f\n", ret);

    ret = sub(a, b); //减
    printf("sub: ret = %f\n", ret);

    ret = mul(a, b); //乘
    printf("mul: ret = %f\n", ret);
    ret = div(a, b);
    printf("div: ret = %f\n", ret);

    ret = power(a);  //除
    printf("power: ret = %f\n", ret);

    return 0;
}
