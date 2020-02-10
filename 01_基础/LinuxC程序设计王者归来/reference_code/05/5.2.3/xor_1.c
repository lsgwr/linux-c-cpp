#include <stdio.h>

int main(void)
{
	int flags = 0xfffffff7;						/* 存储标志位的整型数据 */
	int mask = 0x08;							/* 掩码 */

	printf("the first 0x%x\n", flags=flags ^ mask);	/* 将第3位迅速取反，相当于操作
												一个开关 */
	printf("the second 0x%x\n", flags ^ mask);

	return 0;
}
