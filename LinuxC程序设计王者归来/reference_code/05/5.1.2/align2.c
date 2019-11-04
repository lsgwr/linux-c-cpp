#include <stdio.h>

struct test{
	char ch;
	int i; /* 整型变量放在了两个较小的成员变量中间 */
	short s;
};

int main(void)
{
	struct test var;						  /* 定义一个结构体变量 */
	
	printf("size of var : %d\n", sizeof(var)); /* 计算var变量占用的存储空间 */
	return 0;
}

