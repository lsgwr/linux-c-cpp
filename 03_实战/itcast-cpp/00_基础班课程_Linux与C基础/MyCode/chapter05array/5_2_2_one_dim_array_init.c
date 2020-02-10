/***********************************************************
* @Description : 一位数组的初始化
* @author      : 梁山广(Liang Shan Guang)
* @date        : 2020/1/11 21:22
* @email       : liangshanguang2@gmail.com
***********************************************************/
#include <stdio.h>

#define LEN 10

void print_arr(int arr[], int len) {
    for (int i = 0; i < len; ++i) {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}

int main() {
    int a1[LEN] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0}; // 初始化所有的元素
    print_arr(a1, LEN);
    int a2[10] = {1, 2, 3}; // 指初始化前面的元素，后面的都会被初始化为0
    print_arr(a2, LEN);
    int a3[10] = {0}; // 所有的元素都被初始化为0
    print_arr(a3, LEN);
    return 0;
}
