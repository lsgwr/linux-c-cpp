#include <stdio.h>

int func(int a)
{
	return a + 1; 						/* 返回参数加1 */
}

int main(void)
{
	int res;

	res = func(1) + func(1) + func(1);	/*多次调用函数，计算三次函数调用的结果*/
	printf("the result : %d\n", res);	/*输出变量*/

	return 0;
}

