#include <stdio.h>
#include "public.h"
#include "stu.h"

// 封装学生基本信息的注册对象
static Reg reg = {}; // 初始化为0

//  初始化操作，向公共代码注册学生信息
void Stu_initFunc(int n, Stu buf[])
{
    reg.n = n;
    reg.buf = (void *)buf;
    reg.printf = Stu_printf;
    reg.modify = Stu_modify;

    // 向公共代码注册
    // 所谓注册就是把封装的结构体传递给公共代码，让公共代码通过这些信息来操作学生数据
    registerObjsInfo(&reg); // 注意传递尽量用结构体指针
}

// 本地函数
// 被毁掉的函数，是通过函数指针来调用地，此时完全可以定义为本地函数
// 定义为本地函数可以更好地提高函数的安全性,bug为结构体数组首个元素的指针，也可以认为是结构体数组的名字，可以直接用下标来调用数组内元素

void Stu_modify(int n, void *buf)
{
    int i = 0;
    int stuNum;
    Stu *stu = (Stu *)buf; // 强制转换为Stu *才能进行具体操作 stu此时为结构体数组的指针
    printf("输入学号：");
    scanf("%d", &stuNum);

    for(i=0;i<n;i++){
        if(stu[i].stuNum == stuNum){
            printf("%s %d %f\n", stu[i].name, stu[i].stuNum, stu[i].score);
            printf("输入新信息：\n");
            // name本身就是指针，无需再加&
            scanf("%s %d %f\n", stu[i].name, &stu[i].stuNum, &stu[i].score);
            break;
        }
    }
    if(i==n){
        printf("无此学生\n");
    }
}

/* 显示所有学生的信息
 * n 对象数组的元素个数
 * buf 对象数组的首元素指针，也可以认为是对象数组的数组名，这样就可以用stu[i]来遍历数组了
*/
void Stu_printf(int n, void *buf)
{
    int i = 0;
    Stu *stu = (Stu *)buf;

    for( i = 0; i < n; i++){
        printf("%s %d %f\n", stu[i].name, stu[i].stuNum, stu[i].score);
    }
}
