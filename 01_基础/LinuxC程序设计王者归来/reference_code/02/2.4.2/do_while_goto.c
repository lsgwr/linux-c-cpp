#include <stdio.h>

int main(void)
{
	int n;
	int mul = 1;		/* 用于累计各个整数的乘积 */
	int i;

	scanf("%d", &n);	/* 输入一个整数n */
	
	i = 1;
loop:
	mul *= i;			/* 循环计算n的阶乘，每次将mul乘以循环算子 */
	i++;				/* 循环算子累加 */
	if(i <= n)
		goto loop;		/* 满足循环则跳转到loop标号处执行 */

	printf("the result is %d\n", mul); /* 输出结果 */

	return 0;
}

