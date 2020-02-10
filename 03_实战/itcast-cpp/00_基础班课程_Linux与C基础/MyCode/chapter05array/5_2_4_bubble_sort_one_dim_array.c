/***********************************************************
* @Description : 一位数组的冒泡排序
 * 见自己的笔记 https://gitee.com/lsgwr/algorithms/blob/master/Part1Basic/第2章和第3章总结之常见的排序算法.md#1冒泡排序
* @author      : 梁山广(Liang Shan Guang)
* @date        : 2020/1/11 21:58
* @email       : liangshanguang2@gmail.com
***********************************************************/
#include <stdio.h>

void print_arr(int arr[], int len) {
    for (int i = 0; i < len; ++i) {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}

int main() {
    int a[] = {1, -2, 3, -4, 5, -6, 7, -8, -9, 10};
    int len = sizeof(a) / sizeof(a[0]);
    for (int i = 0; i < len - 1; ++i) {
        for (int j = 0; j < len - 1 - i; ++j) { // 每轮j循环把一个最大的元素放到本轮的最后
            if (a[j] > a[j + 1]) {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
    print_arr(a, len);
    return 0;
}
