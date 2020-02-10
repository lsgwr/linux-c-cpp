#include <stdio.h>

int count = 0;			/* 全局变量 */

int func(int a)
{
	count++;			/* func函数内部操作 */
	return a + 1;		/* 返回参数加1 */
}

int main(void)
{
	int res;

	res = 3 * func(1);	/* 只调用一次func函数，并使用函数的返回值进行乘法运算 */
	
	printf("the count : %d\n", count);	/* 输出全局变量的值 */
	printf("the result : %d\n", res);	/* 输出函数返回值的和 */

	return 0;

}

