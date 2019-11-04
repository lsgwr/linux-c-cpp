#include <stdio.h>

/* 定义一个inline函数add，执行两个数据的加法，返回两个数的和 */
inline int f(int a, int b)
{
	return a + b;
}

int main(void)
{
	int c;

	c = f(1,2); /* 调用inline函数，这部分内容在inline函数展开时会被add函数的
				代码所取代 */
	
	return 1;
}

