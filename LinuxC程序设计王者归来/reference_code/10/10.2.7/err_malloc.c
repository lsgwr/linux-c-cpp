#include <stdio.h>
#include <stdlib.h>
/* 错误的函数，参数指针p的值并未改变 */
void f1(int *p)
{
	p = (int *)malloc(sizeof(int));
}
int main(void)
{
	int *p;
	f1(p); /* 分配内存空间 */
	printf("set heap\n");
	/* 注意这里的p指向的是一块未知区域，不是刚刚分配的内存空间 */
	*p = 4;
	free(p); /* 释放内存 */
	return 0;
}
