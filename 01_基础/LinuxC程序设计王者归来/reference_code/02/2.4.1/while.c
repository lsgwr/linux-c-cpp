#include <stdio.h>

int main(void)
{
	int n;
	int mul = 1;		/* 用于累计各个整数的乘积 */
	int i;

	scanf("%d", &n);	/* 输入一个整数n */
	
	i = 1;
	while(i <= n){	/* 循环计算n的阶乘，每次将mul乘以循环算子 */
		mul *= i;	/* 累计乘积 */
		i++;
	}

	printf("the result is %d\n", mul); /* 输出结果 */

	return 0;
}

