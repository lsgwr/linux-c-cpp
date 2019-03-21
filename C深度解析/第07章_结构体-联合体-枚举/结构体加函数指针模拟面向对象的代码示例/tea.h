#ifndef H_TEA_H
#define H_TEA_H

/* 教师结构体 */
typedef struct Teacher
{
    char name[20];  //名字
    int teaNum;     //教师编号
    int grade;      //级别
}Tea;

extern void Tea_initFun(int n, Tea buf[]);
static void Tea_alter(int n, void *buf);
static void Tea_print(int n, void *buf);

#endif
