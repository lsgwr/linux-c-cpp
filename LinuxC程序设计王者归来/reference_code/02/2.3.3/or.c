#include <stdio.h>

int main(void)
{
	int a = 200; 				/* 一个变量 */
	int *p = NULL;				/* 一个指针 */

	/* 程序的功能与程序2-1完全相同，只是程序的执行逻辑不相同 */
	p = &a;						/* 将p指向变量a */
	if(p == NULL || *p != 100)	/* 判断p指向一个变量，并且这个变量的值是否是
								100 */
		printf("hi\n");
	else
		printf("hello\n");		/* 输出提示信息 */

	return 0;
}

