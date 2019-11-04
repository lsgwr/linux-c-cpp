#include <stdio.h>

int main(void)
{
	int n;
	int add = 0;				/* 累计加法的结果 */
	int i;

	scanf("%d", &n);			/* 输入一个整数n */

	for(i = 1; i <= 10; i++)	/* 循环算子初始化，条件判断和循环算子递增 */
		add += i;				/* 累计和 */

	printf("the result is %d\n", add); /* 输出结果 */

	return 0;
}

