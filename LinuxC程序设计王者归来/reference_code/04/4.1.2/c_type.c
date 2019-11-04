#include <stdio.h>

struct test{ /* 定义一个结构体 */
	int a;
	int b;
	int c;
};

int main(void)
{
	int a[10];
	int *p;
	struct test var;						/* 结构体变量 */

	printf("array : %d\n", sizeof(a));		/* 输出数组占用的字节数 */
	printf("pointer: %d\n", sizeof(p));	/* 输出指针占用的字节数 */
	printf("struct : %d\n", sizeof(var));	/* 输出结构变量占用的字节数 */
	return 0;
}

