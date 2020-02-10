/***********************************************************
 * @Description : 结构体数组
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/14 7:40
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>
#include <string.h>

// 统计学生成绩
struct stu {
    int num;
    char name[20];
    char sex;
    double score;
};

int main() {
    struct stu students[5] = {
            {101, "张三",   'M', 45},
            {102, "李四",   'M', 62.5},
            {103, "王五",   'F', 92.5},
            {104, "Jack", 'F', 87},
            {105, "Rose", 'M', 58},
    };
    int c = 0;
    double ave, sum = 0;
    for (int i = 0; i < 5; ++i) {
        sum += students[i].score; // 计算总分
        if (students[i].score < 60) {
            c++; // 统计不及格的人数
        }
    }
    printf("平均分 = %f，不及格人数为：%d\n", sum/5, c);
    for (int i = 0; i < 5; ++i) {
        printf("name = %s, score = %f\n", students[i].name, students[i].score);
    }
    return 0;
}

