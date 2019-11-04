#include <stdio.h>

int main(void)
{
	int n;
	int mul = 1; 		/* 用于累计各个整数的乘积 */
	int i;
	int t;

	scanf("%d", &n);	/* 输入一个整数n */
	
	i = 1;
	t = i <= n;
	if(t == 0) 			/* 表达式的值为假则结束循环 */
		goto done;
loop:
	mul *= i; 			/* 执行循环语句 */
	i++;
	t = i <= n;
	if(t == 1) 			/* 如果条件表达式满足则跳转到loop，否则顺序执行退出循环 */
		goto loop;

done:
	printf("the result is %d\n", mul); /* 输出结果 */

	return 0;
}

