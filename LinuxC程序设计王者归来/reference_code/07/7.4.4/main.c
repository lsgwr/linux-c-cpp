#include <stdio.h>
#include "static_lib.h" /* 包含static_lib.a库中函数声明的头文件，这样就可以引
						 用用这些函数了 */

int main(void)
{
	int a, b;

	printf("please input a and b\n");
	scanf("%d%d", &a, &b);
	printf("the add : %d\n", add(a, b)); /* 调用加法函数 */
	printf("the sub : %d\n", sub(a, b)); /* 调用减法函数 */
	printf("the mul : %d\n", mul(a, b)); /* 调用乘法函数 */
	printf("the div : %d\n", div(a, b)); /* 调用除法函数 */

	return 0;
}
