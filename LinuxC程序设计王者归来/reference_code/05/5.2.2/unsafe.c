#include <stdio.h>
int main(void)
{
	int a = 0x3; /* 在16位体系结构上运行，这时整型a占用2个字节 */
	int b = 0xfffe;

	printf("the result is : 0x%x\n", a & b); /* 输出与掩码"位与"后的结果 */

	return 0;
}
