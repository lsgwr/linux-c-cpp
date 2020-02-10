#include <stdio.h> 
int main(void)
{
	int input =0; /* 一个整型变量 */
	printf("Input an integer:"); 
	scanf("%d", input); /* 将一个输入的字符串保存在没有地址空间的位置上 */
	printf("The integer you input is %d\n", input); /* 程序不会执行到这里 */
	return 0;
}
