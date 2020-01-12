/***********************************************************
 * @Description : 数组名作为函数形参
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 20:02
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>

void printArr(int a[], int len){
    for (int i = 0; i < len; ++i) {
        printf("%d\t", a[i]);
    }
}

int main() {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int len = sizeof(a) / sizeof(a[0]);
    printArr(a, len);
    return 0;
}
