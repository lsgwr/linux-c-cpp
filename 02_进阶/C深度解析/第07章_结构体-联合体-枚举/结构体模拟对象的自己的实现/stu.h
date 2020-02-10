#ifndef STU_H_INCLUDED
#define STU_H_INCLUDED

/* 学生结构体 */
typedef struct Student
{
    // 姓名
    char name[20];
    // 学号
    int stuNum;
    // 分数
    float score;
}Stu;


/* 学生函数的声明 */

//  全局函数
extern void Stu_initFunc(int n, Stu buf[]);

// 本地函数
// 被毁掉的函数，是通过函数指针来调用地，此时完全可以定义为本地函数
// 定义为本地函数可以更好地提高函数的安全性
static void Stu_modify(int n, void *buf); // buf为空指针是为了方便和public里面的类型兼容

static void Stu_printf(int n, void *buf);

#endif // STU_H_INCLUDED
