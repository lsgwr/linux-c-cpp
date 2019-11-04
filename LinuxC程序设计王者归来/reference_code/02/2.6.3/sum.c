#include <stdio.h>

int main(void)
{
	int i;
	int sum;				/* 保存输入的变量 */
	int n;

	scanf("%d", &n);		/* 输入一个n值 */

	sum = 0;
	for(i = 1; i <= n; i++)	/* 使用一个循环计算1到n之间所有整数的值 */
		sum += i;

	printf("the result is : %d\n", sum); /* 输出结果 */

	return 0;
}

