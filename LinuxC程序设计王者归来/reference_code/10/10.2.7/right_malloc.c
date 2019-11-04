#include <stdio.h>
#include <stdlib.h>
/* 正确的函数，传入p的引用，参数指针p的值改变 */
void f1(int **p)
{
	*p = (int *)malloc(sizeof(int)); /* 修改p指针的值 */
}
int main(void)
{
	int *p;
	f1(&p);							/* 分配内存空间 */
	printf("set heap\n");
	*p = 4;							/* 对堆上变量进行赋值 */
	printf("the heap %d\n", *p);	/* 输出堆上变量的值 */
	free(p);						/* 释放内存 */
	return 0;
}
