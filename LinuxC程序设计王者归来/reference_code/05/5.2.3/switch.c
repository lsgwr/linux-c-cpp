#include <stdio.h>

#define swap(a, b){		/* 使用异或交换两个变量的值 */\
	(a) = (a) ^ (b); \
	(b) = (b) ^ (a); \
	(a) = (a) ^ (b); \
}

int main(void)
{
	int a, b;

	a = 2; 		/* 测试用的临时变量 */
	b = 3;
	swap(a, b);	/* 交换两个变量 */
	printf("a is : %d, b is : %d\n", a, b);

	return 0;
}
