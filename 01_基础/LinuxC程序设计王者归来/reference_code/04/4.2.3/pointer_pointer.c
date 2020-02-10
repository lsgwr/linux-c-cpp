#include <stdio.h>

int main(void)
{
	int a;
	int *p;
	int **q;

	a = 100;									/* 变量a */
	p = & a;									/* p指向变量a */
	q = &p;										/* q指向指针p */

	printf("var a : %d\n", a); 					/* 输出变量的值 */
	printf("pointer p : 0x%x\n", *p);			/* 输出指针的值 */
	printf("pointer pointer q : 0x%x\n", *q);	/* 输出指针的指针的值 */

	return 0;
}

