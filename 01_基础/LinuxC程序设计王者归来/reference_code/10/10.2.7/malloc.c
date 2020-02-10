#include <stdio.h>
#include <stdlib.h>
/* 在函数中分配一块内存 */
void f1(int **p)
{
	*p = (int *)malloc(sizeof(int));
}
/* 在另外一个函数中对分配的内存进行赋值 */
void f2(int *p)
{
	printf("the heap is %d\n", *p);
}
int main(void)
{
	int *p;
	f1(&p);		/* 分配内存空间 */
	*p = 4;
	f2(p);		/* 对内存空间进行赋值 */
	free(p);	/* 释放后指针p仍然指向那片内存区域 */
	f2(p); 
	return 0;
}
