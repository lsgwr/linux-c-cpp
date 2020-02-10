#include <stdio.h>

int main(void)
{
	unsigned char a, b;
	unsigned char mask = 0x38;	/* 二进制的00111000 */
	
	a = 0xff;					/* 测试用的数据 */
	
	b = a & mask;				/* 使用掩码得出数据a的第4~6位 */
	printf("the flag b is : 0x%x\n",b);
	
	return 0;
}
