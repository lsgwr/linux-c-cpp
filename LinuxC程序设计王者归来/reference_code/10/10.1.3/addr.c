#include <stdio.h>
int main()
{
	int a; /* 第一个变量 */
	int b; /*第二个变量*/
	printf("the first address : 0x%x\n",  &a); /* 打印的第一个变量的地址 */
	printf("the second address : 0x%x\n",  &b); /*打印的第二个变量的地址*/
	return 0;
}
