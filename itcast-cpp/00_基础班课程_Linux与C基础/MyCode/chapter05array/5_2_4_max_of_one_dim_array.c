/***********************************************************
* @Description : 一位数组的最值
* @author      : 梁山广(Liang Shan Guang)
* @date        : 2020/1/11 21:47
* @email       : liangshanguang2@gmail.com
***********************************************************/
#include <stdio.h>

int main() {
    int a[] = {1, -2, 3, -4, 5, -6, 7, -8, -9, 10};
    int max = a[0]; // 不能随意初始化
    int len = sizeof(a) / sizeof(a[0]);
    for (int i = 0; i < len; ++i) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    printf("最大值为:%d\n", max);
    return 0;
}
