#include "common.h"
/* 全局变量定义 */
int (*p1)(int ,int) = NULL; 
int (*p2)(int ,int) = NULL;
int (*p3)(int ,int) = NULL; 
int (*p4)(int ,int) = NULL;

/* 四则运算的函数 */
/* 加法函数 */
int add(int a, int b)
{
	return a + b;
}

/* 减法函数 */
int sub(int a, int b)
{
	return a - b;
}

/* 乘法函数 */
int mul(int a, int b)
{
	return a * b;
}

/* 除法函数 */
int div(int a, int b)
{
	return a / b;
}
