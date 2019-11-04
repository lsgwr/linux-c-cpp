#include <stdio.h>

void f(void);	/* 函数的声明 */

int a = 123;	/* 全局变量的定义 */

int main(void)
 {
	f( );		/* 调用函数 */
	printf("a = %d\n",a); /* 输出全局变量 */

	return 0;
}

