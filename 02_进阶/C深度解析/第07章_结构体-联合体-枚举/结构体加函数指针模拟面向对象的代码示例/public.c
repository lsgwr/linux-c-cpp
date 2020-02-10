#include <stdio.h>
#include "public.h"

//保存差异代码注册的"reg"结构体,里面等封装了操作信息
struct Register *regp = NULL;

/* 注册函数,注册的过程就是记录下"差异代码"传递过来的reg的指针 */
void registerFun(struct Register *reginfo)
{
    regp = reginfo;
}

/* 显示所有信息 */
void printFun(void)
{
    /* 通过注册的reg信息, 通过函数指针, 调用差异代码的"显示函数",
     * 如果注册的是"学生操作信息",调用的就是学生的"显示函数",否者就是老师的"显示函数"
     * 
     * 调用时, 将"数组元素个数"和"数组首元素指针"传递给下层的差异代码,
     * 差异代码拿到"数组"后,就可以操作数组中的数据了
     */
    regp->print(regp->n, regp->buf);
}

void alterFun(void)
{
    /* 修改数据,操作原理是一样的 */
    regp->alter(regp->n, regp->buf);
}
