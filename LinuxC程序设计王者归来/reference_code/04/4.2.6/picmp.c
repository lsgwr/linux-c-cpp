#include <stdio.h>

int main(void)
{
	int *p;
	
	if(p == 1000) /* 直接拿整型常量和指向整型的指针进行比较 */
		printf("equal\n");
	else
		printf("not equal\n");

	if(p == (int *)1000) /* 将整型常量转化为指向整型变量的指针之后再比较 */
		printf("equal\n");
	else
		printf("not equal\n");

	return 0;
}

