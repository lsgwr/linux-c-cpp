#include <stdio.h>

int main(void)
{
	int i;
	int sum; /* 保存结果 */
	int n;
	scanf("%d", &n); 			/* 输入一个n的值 */

	sum = ((1 + n) * n) / 2;	/* 使用高斯公式计算1到n之间所有整数的和 */

	printf("the result is : %d\n", sum); /* 输出运行的结果 */

	return 0;
}

