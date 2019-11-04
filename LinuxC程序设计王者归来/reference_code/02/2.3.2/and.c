#include <stdio.h>

int main(void)
{
	int a = 200; 				/* 一个变量 */
	int *p = NULL;				/* 一个指针 */

	p = &a;						/* 将p指向变量a */
	if(p != NULL && *p == 100)	/* 判断p指向一个变量，并且这个变量的值是否是
                                    	100 */
		printf("hello\n");
	else
		printf("hi\n"); 		/* 输出另一个提示信息 */

	return 0;
}

