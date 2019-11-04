#include <stdio.h>

int right_shift(int a, int n)
{
	int b, c;
	
	b = a << (32 - n);		   /* 保留a的低n位 */
	c = a >> n;
	c = c & ~(~0 << (32 - n)); /* 保证c的高位不会出现由于移位产生的"1"的干扰 */
	c = c | b; 				   /* 将两个部分拼接，完成循环右移 */

	return c;
}

int main(void)
{
	int a, b;
	
	printf("please input a interger\n");
	scanf("%d", &a);           /* 输入一个整数a */
	
	printf("the original : 0x%x\n", a);

	b = right_shift(a, 4);				/* 循环移4位 */
	printf("the result : 0x%x\n", b);	/* 以十六进制形式打印结果，便于观察 */
}

