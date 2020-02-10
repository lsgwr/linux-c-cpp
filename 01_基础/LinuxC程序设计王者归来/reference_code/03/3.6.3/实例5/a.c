#include<stdio.h>
void f(void);
int a = 123; 							/* 全局变量的定义 */
int b = 121;
int main()
{
	f( ); 								/* 调用函数f */
	printf("a = %d, b = %d\n", a, b);	/* 输出变量a和b */
	return 0;
}

