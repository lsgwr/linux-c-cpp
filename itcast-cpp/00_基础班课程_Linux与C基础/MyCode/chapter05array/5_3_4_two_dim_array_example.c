/***********************************************************
* @Description : 二位数组应用：成绩统计
* @author      : 梁山广(Liang Shan Guang)
* @date        : 2020/1/12 12:12
* @email       : liangshanguang2@gmail.com
***********************************************************/
#include <stdio.h>

#define ROW 5
#define COL 3

int main() {
    // 行代表人：老大到老五
    // 列代表科目：语、数、外
    float a[5][3] = {
            {80, 75, 56},
            {59, 65, 71},
            {59, 63, 70},
            {85, 45, 90},
            {76, 77, 45}
    };
    // 各科不及格的人数
    int person_low[3] = {0};
    float sum = 0;
    // 各科的平均成绩
    float lesson_aver[3] = {0};
    for (int j = 0; j < COL; ++j) {
        for (int i = 0; i < ROW; ++i) {
            sum = sum + a[i][j];
            if (a[i][j] < 60) {
                person_low[j]++;
            }
        }
        lesson_aver[j] = sum / 5;
        sum = 0;
    }
    printf("各科的平均成绩：");
    for (int i = 0; i < 3; ++i) {
        printf("%.2f\t", lesson_aver[i]);
    }
    printf("\n");
    printf("各科不及格的人数：");
    for (int i = 0; i < 3; ++i) {
        printf("%d\t", person_low[i]);
    }
    return 0;
}
