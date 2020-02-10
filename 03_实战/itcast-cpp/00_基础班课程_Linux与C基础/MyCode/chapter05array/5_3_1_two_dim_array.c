/***********************************************************
* @Description : 二位数组的定义和使用
* @author      : 梁山广(Liang Shan Guang)
* @date        : 2020/1/12 10:40
* @email       : liangshanguang2@gmail.com
***********************************************************/
#include <stdio.h>

#define ROW 3
#define COL 4

/**
 * 打印二维数组
 * 如何传递二维数组很重要
 * @param a 二维数组
 * @param row 行数
 * @param col 列数
 */
void print_arr(int (*a)[COL]) {
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            printf("%d\t", a[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int a[ROW][COL];
    int num = 0;
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            a[i][j] = num++;
        }
    }
    print_arr(a);
    return 0;
}
