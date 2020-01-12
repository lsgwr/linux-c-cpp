/***********************************************************
* @Description : 二位数组的初始化
* @author      : 梁山广(Liang Shan Guang)
* @date        : 2020/1/12 10:49
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
    printf("1.分段赋值\n");
    int a1[3][4] = {
            {1, 2,  3,  4},
            {5, 6,  7,  8},
            {9, 10, 11, 12}
    };
    show_arr(a1);

    printf("2.连续赋值\n");
    int a2[ROW][COL] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    show_arr(a2);

    printf("3.可以只给部分元素赋初值，未初始化则为0\n");
    int a3[ROW][COL] = {1, 2, 3, 4};
    show_arr(a3);

    printf("4.所有的成员都设置为0\n");
    int a4[ROW][COL] = {0};
    show_arr(a4);

    printf("[]中不定义元素个数，定义时必须初始化：\n");
    int a5[][COL] = {1, 2, 3, 4, 5, 6, 7, 8};
    show_arr(a5);
    return 0;
}
