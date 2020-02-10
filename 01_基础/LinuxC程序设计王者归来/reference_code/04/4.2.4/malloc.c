#include <stdio.h>
#include <stdlib.h>

/* 使用指针作为参数，可以实现交换两个变量的值 */
void alter(int ** p)
{
	int *q;
	
	q = (int *)malloc(sizeof(int)); /* 分配一块内存，该内存用于存储一个整型变量 */

	*q = 100;	/* 将该变量值设置为100 */

	*p = q;		/* 使指针的指针所指向的内容指向这块新的内存区域 */
}

int main(void)
{
	int a;
	int *p;

	a = 10;		/* 变量a */
	p = &a;		/* 指针p指向变量a */

	printf("p : 0x%x, *p %d\n", p, *p);
	alter(&p);	/* 更改指针变量本身的值 */
	printf("p : 0x%x, *p %d\n", p, *p);

	return 0;
}

