#include <stdio.h>

int add(int a, int b)
{
	return a + b;	/* 全局变量b的作用域达不到这里，因此add函数看不到全局变量b */
}

int b = 10;			/* 定义一个全局变量b，以后的函数可以应用这个全局变量 */

int mul(int a)
{
	return a * b;	/* 在mul函数中引用全局变量b */
}

int main(void)
{
	int res1;							/* 保存结果的临时变量 */
	int res2;

	res1 = add(1, 5);					/* 调用add函数 */
	res2 = mul(1);						/* 调用mul函数 */

	printf("res1 : %d, res2 : %d\n", res1, res2);
	printf("the global b : %d\n", b);	/* 在main函数中引用全局变量b */

	return 0;
}

