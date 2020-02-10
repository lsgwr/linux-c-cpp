#ifndef TEA_H_INCLUDED
#define TEA_H_INCLUDED

/* 老师结构体 */
typedef struct Teacher
{
    // 姓名
    char name[20];
    // 教师编号
    int teaNum;
    // 级别
    int level;
}Tea;


/* 学生函数的声明 */

//  全局函数
extern void Tea_initFunc(int n, Tea buf[]);

// 本地函数
// 被毁掉的函数，是通过函数指针来调用地，此时完全可以定义为本地函数
// 定义为本地函数可以更好地提高函数的安全性
static void Tea_modify(int n, void *buf); // buf为空指针是为了方便和public里面的类型兼容

static void Tea_printf(int n, void *buf);

#endif // TEA_H_INCLUDED
