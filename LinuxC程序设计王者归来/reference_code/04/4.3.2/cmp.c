#include "common.h"

int cmp_int(void *p, void *q)
{
	int *a, *b;
	a = (int *)p; /* 将参数中void *类型的指针转换为int型的指针 */
	b = (int *)q;
	
	if(*a > *b) /* 比较两个值的大小 */
		return 1;
	else if(*a < *b)
		return -1;
	else
		return 0;
}

int cmp_struct(void *p, void *q)
{
	Book a, b;
	
	a = (Book)p; /* 将参数中void *类型的指针转换为Book类型的指针 */
	b = (Book)q;

	if(a->id > b->id) /* 比较成员变量id的大小 */
		return 1;
	else if(a->id < b->id)
		return -1;
	else
		return 0;
}
