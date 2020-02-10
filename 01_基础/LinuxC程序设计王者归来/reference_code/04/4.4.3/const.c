#include <stdio.h>

int main(void)
{
	int const a = 100; 			/* 常量变量a */
	
	a = 200;
	printf("a is : %d\n", a);	/* 尝试改变一个常量变量的值 */

	return 0;
}

