/***********************************************************
* @Description : 一位数组的最值
* @author      : 梁山广(Liang Shan Guang)
* @date        : 2020/1/11 21:47
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
    int i = 0;
    int j = len - 1;
    while (i < j) {
        int tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
        i++;
        j--;
    }
    print_arr(a, len);
    return 0;
}
