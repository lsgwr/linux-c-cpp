#include <stdio.h>

int func(int a)
{
	return a + 1;		/* 返回参数加1 */
}

int main(void)
{
	int res;

	res = 3 * func(1);	/* 只调用一次func函数，并使用函数的返回值进行乘法运算 */
	printf("the result : %d\n", res); /* 输出结果 */

	return 0;
}

