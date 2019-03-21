#include <stdio.h>
#include "public.h"

// 保存差异代码注册的结构体，里面封装了操作信息
Reg *regp = NULL;

/* 注册函数，注册过程就是记录下“差异代码”传过来的reg指针 */
void registerObjsInfo(Reg *regpFromSon)
{
    regp = regpFromSon;
}


/* 显示所有信息 */
void printfFunc(void)
{
    /*
     * 通过注册的regp信息，借用函数指针调用子类的显示函数，
     * 并把数据元素个数和数组首元素传给子类printf函数
     */
    regp->printf(regp->n, regp->buf);
}

void modifyFunc(void)
{
    /*
     * printfFunc的原理是一样的
     */
     regp->modify(regp->n, regp->buf);
}


