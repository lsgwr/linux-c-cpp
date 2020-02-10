#ifndef H_STU_H
#define H_sTU_H

/* 学生结构体 */
typedef struct Student
{
    char name[20];  //名字
    int stuNum;     //学号
    float score;    //分数
}Stu;

/* 学生函数的声明 */
//全局函数
extern void Stu_initFun(int n, stu buf[]);  //全局函数

//本地函数
//被毁掉的函数,是通过函数指针来调用的,此时完全可以定
//义为本地函数,定义为本地函数,可以更好的提高函数的安全性
static void Stu_alter(int n, void *buf);
static void Stu_print(int n, void *buf);

#endif
