#include <stdio.h>

#define a *p	/* 定义两个别名 */
#define b *q

int main(void)
{
	int x;
	int *p, *q;	/* 定义两个指针 */

	p = &x;
	q = &x;		/* 两个指针指向同一块内存区域 */

	a = 2;
	b = 3;		/* 两次赋值会将同一个变量x的值覆盖 */
	
	printf("the value is : %d\n", a + b); /* 输出结果 */

	return 0;
}

