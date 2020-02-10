#include <stdio.h>

void f(void);	/* 函数的声明 */

int a;			/* 全局变量的声明 */

int main(void)
{
	a = 123;
	f( );		/* 调用函数 */
	printf("a = %d\n",a);

	return 0;
}

