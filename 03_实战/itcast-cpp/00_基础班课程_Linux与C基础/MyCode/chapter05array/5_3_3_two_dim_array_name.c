/***********************************************************
* @Description : 二位数组名
* @author      : 梁山广(Liang Shan Guang)
* @date        : 2020/1/12 11:03
* @email       : liangshanguang2@gmail.com
***********************************************************/
#include <stdio.h>

#define ROW 3
#define COL 4

/**
 * 打印二维数组
 * 如何传递二维数组很重要
 * @param a 二维数组
 */
void show_arr(int (*a)[COL]) {
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            printf("%d\t", a[i][j]);
        }
        printf("\n");
    }
}

int main() {
    printf("二维数组本质上还是一位数组，此一位数组有3个元素，每个元素又是一个一位数组int[4]\n");
    int a[ROW][COL] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    printf("数组名为数组首元素地址，二维数组第0个元素为一位数组\n");
    printf("1.第0个一位数组的数组名为a[0]：");
    printf("a=%p\t", a);
    printf("a[0]=%p\n", a[0]);
    printf("二维数组所占内存空间，有3个一维数组，每个一维数组的空间为4*4(4个元素*每个整型有4位):");
    printf("sizeof(a)=%lu\n", sizeof(a)); // 3*3*4 = 48
    printf("第0个元素所占内存空间，a[0]为第0个一维数组int[4]的数组名，4个元素*每个整型有4位=16：");
    printf("sizeof(a[0])=%lu\n", sizeof(a[0]));
    printf("第0行0列元素所占内存空间，第0行0列元素为一个int类型，4字节：");
    printf("sizeof(a[0][0])=%lu\n", sizeof(a[0][0]));
    printf("二维数组行数：row=%lu\n", sizeof(a) / sizeof(a[0]));
    printf("二维数组列数：col=%lu\n", sizeof(a[0]) / sizeof(a[0][0]));
    printf("二维数组元素总数即行数*列数n=%lu\n", sizeof(a) / sizeof(a[0][0]));
    return 0;
}
