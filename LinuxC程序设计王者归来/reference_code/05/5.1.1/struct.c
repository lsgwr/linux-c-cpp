#include <stdio.h>

struct test{			/* 声明一个结构体变量 */
	int array[5];
	int a;
	int *p;
};						/* 声明完毕 */

int main(void)
{	
	struct test var;	/* 定义一个结构体变量 */
	int i;

	/* 输出结构体成员变量的地址 */
	for(i = 0; i < 5; i++)
		printf("array [%d] : 0x%x\n", i + 1, (unsigned int)&(var.array[i]));
									 /* 输出数组的地址 */
	printf("a : 0x%x\n", (unsigned int)&(var.a)); /* 输出整型变量a的地址 */
	printf("p : 0x%x\n", (unsigned int)&(var.p)); /* 输出指针变量p的地址 */

	return 0;
}
