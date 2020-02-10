#ifndef H_PUBLIC_H 
#define H_PUBLIC_H


/* 用于向公共代码注册操作信息的结构体 */
struct Register
{
    void *buf;      //数组第一个元素的地址
    int n;          //数组元素个数

    void (*print)(); //打印函数的指针
    void (*alter)(); //修改函数的指针
};

extern void registerFun(struct Register *reginfo);
extern void printFun(void);
extern void alterFun(void);

#endif
