#include <stdio.h>
#include "public.h"
#include "tea.h"

// 封装老师基本信息的注册对象
static Reg reg = {}; // 初始化为0

//  初始化操作，向公共代码注册老师信息
void Tea_initFunc(int n, Tea buf[])
{
    reg.n = n;
    reg.buf = (void *)buf;
    reg.printf = Tea_printf;
    reg.modify = Tea_modify;

    // 向公共代码注册
    // 所谓注册就是把封装的结构体传递给公共代码，让公共代码通过这些信息来操作学生数据
    registerObjsInfo(&reg); // 注意传递尽量用结构体指针
}

// 本地函数
// 被毁掉的函数，是通过函数指针来调用地，此时完全可以定义为本地函数
// 定义为本地函数可以更好地提高函数的安全性,bug为结构体数组首个元素的指针，也可以认为是结构体数组的名字，可以直接用下标来调用数组内元素

void Tea_modify(int n, void *buf)
{
    int i = 0;
    int teaNum;
    Tea *tea = (Tea *)buf; // 强制转换为Tea *才能进行具体操作 tea此时为结构体数组的指针
    printf("输入教师编号：");
    scanf("%d", &teaNum);

    for(i=0;i<n;i++){
        if(tea[i].teaNum == teaNum){
            printf("%s %d %d\n", tea[i].name, tea[i].teaNum, tea[i].level);
            printf("输入新信息：\n");
            scanf("%s %d %d\n", tea[i].name, &tea[i].teaNum, &tea[i].level);
            break;
        }
    }
    if(i==n){
        printf("无此老师\n");
    }
}

/* 显示所有老师的信息
 * n 对象数组的元素个数
 * buf 对象数组的首元素指针，也可以认为是对象数组的数组名，这样就可以用tea[i]来遍历数组了
*/
void Tea_printf(int n, void *buf)
{
    int i = 0;
    Tea *tea = (Tea *)buf;

    for( i = 0; i < n; i++){
        printf("%s %d %d\n", tea[i].name, tea[i].teaNum, tea[i].level);
    }
}
