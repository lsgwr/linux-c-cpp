#include <stdio.h>

/* 交换两个变量的函数 */
void swap(int a, int b) 
{
	int t;
	
	t = a; 							/* 交换两个变量，使用临时变量 */
	a = b;
	b = t;
}

int main(void)
{
	int a, b;

	a = 1;
	b = 2;

	printf("a, b : %d, %d\n", a, b);	/* 输出交换前的值 */
	swap(a, b);						/* 交换两个参数 */
	printf("a, b : %d, %d\n", a, b);	/* 输出交换后的结果 */
 
	return 0;
}

