#include <stdio.h>
int a = 1; /* 其地址为数据段的首地址 */
int main(void)
{
	int b; /* 其地址为栈的末地址 */
	/* 打印栈的首地址，使用栈的末地址向上推导。
	* 跳过仅有的一个自动变量b，即可得到栈的首地址 
	*/
	printf("stack %x\n", &b + 4); 
	/* 打印数据段的首地址，使用数据段的首地址向上推导。
	* 跳过仅有的一个全局变量a，即可得到堆的首地址 
	*/
	printf("data %x\n", &a + 4); 
	/* 打印栈和堆的首地址的差，得到进程空间的大小 */
	printf("process space %u\n", (&b + 4) - (&a + 4));
	return 0;
}
