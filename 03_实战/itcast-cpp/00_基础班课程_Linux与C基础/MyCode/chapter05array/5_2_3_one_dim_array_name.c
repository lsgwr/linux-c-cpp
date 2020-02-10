/***********************************************************
* @Description : 数组名是一个地址的常量，代表数组中首元素的地址
* @author      : 梁山广(Liang Shan Guang)
* @date        : 2020/1/11 21:35
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
    int arr[LEN] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // 初始化所有的元素
    printf("arr=%p\n", arr); // 数组名是一个指针

    int n = sizeof(arr); // 数组占用内存的大小，LEN个int类型，10*4=40
    printf("数组占用的字节数:%d\n", n);
    int n0 = sizeof(arr[0]); // 数组第0个元素占用内存大小，第0个元素为int，4
    printf("数组中每个元素占用的字节数:%d\n", n0);
    int len = sizeof(arr) / sizeof(arr[0]);
    printf("数组长度为：%d\n", len);
    printf("利用数组长度遍历数组:");
    for (int i = 0; i < len; ++i) {
        printf("%d\t", arr[i]);
    }
    printf("\n");
    return 0;
}
