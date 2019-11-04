#include <stdio.h>

int main(void)
{
	int a = 32;
	int x = 0xFFFFFFFF;						/* 一个无符号整型 */
	
	printf("%d\n",  0xFFFFFFFF >> 32) ;		/* 右移32位，结果未定义 */
	printf("%d\n",  x >> 32) ;				/* 右移32位，结果未定义 */
	printf("%d\n",  0xFFFFFFFF >> a) ;		/* 右移32位，结果未定义 */

	return 0;
}

