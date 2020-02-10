#include <stdio.h>
int main(void)
{
	int a = 0x12345678;					/* 测试用的数据 */
	char *p;
	p = (char *)(&a);					/* 将a的指针转换 */
	if(*p == 0x78)
		printf("The little endian\n");	/* 输出小端法 */
	else
		printf("The big endian\n");		/* 输出大端法 */
	return 0;
}
