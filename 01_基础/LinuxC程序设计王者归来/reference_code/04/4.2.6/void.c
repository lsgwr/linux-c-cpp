#include <stdio.h>

int main(void)
{
	int a = 100;		/* 局部变量a */
	void *p;
	
	p = &a;				/* p指向变量a，a的值是100 */
	
	printf("%d\n", *p);	/* 引用p所指向的数据 */

	return 0;
}

