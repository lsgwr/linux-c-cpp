#include <stdio.h>

int main(void)
{
	int a, b;

	scanf("%d%d", &a, &b);	/* 输入变量a和b的值 */

	if(a > b)				/*使用一个条件判断*/
		printf("a is higher than b\n");
	else					/* 如果a小于b则输出另一些信息 */
		printf("a is lower than b\n");

	return 0;
}

