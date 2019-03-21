#ifndef PUBLIC_H_INCLUDED
#define PUBLIC_H_INCLUDED

/* 用于向公共代码注册操作信息的结构体 */
typedef struct Register
{
    void *buf; // 对象数组第一个元素的地址
    int n; // 对象数组的元素个数

    void (*modify)(); // 修改函数的函数指针
    void (*printf)(); // 打印函数的函数指针
}Reg;

extern void registerObjsInfo(Reg *reg);

extern void printfFunc(void);

extern void modifyFunc(void);

#endif // PUBLIC_H_INCLUDED
