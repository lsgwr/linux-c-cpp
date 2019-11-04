#include <stdio.h>

int main(void)
{
	int i;
	int sum; /* 定义一个局部变量，该局部变量作为一个累加和的临时值 */
	
	for(i = 1; i <= 10; i++)
		sum += i;						/* 每次累加i */

	printf("the sum is : %d\n", sum);	/* 输出运算结果 */

	return 0;
}

