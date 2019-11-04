#include <stdio.h>

void swap(int * a, int * b)
{
	int t;
	
	t = *a; /* 使用指针作为参数，可以实现交换两个变量的值 */
	*a = *b;
	*b = t;
}

int main(void)
{
	int a, b;

	a = 1;							/* 两个临时变量 */
	b = 2;

	printf("a, b : %d, %d\n", a, b);	/* 输出交换前的变量 */
	swap(&a, &b);					/* 交换两个参数 */
	printf("a, b : %d, %d\n", a, b);	/* 输出交换后的变量 */
	return 0;
}

