#include <stdio.h>

struct test{			/* 声明一个结构体变量 */
	char ch;
	short s;
	int i;
};						/* 声明完毕 */

int main(void)
{
	struct test var;	/* 定义一个结构体变量 */
	
	printf("size of var : %d\n", sizeof(var)); /* 计算var变量占用的存储空间 */

	return 0;
}
