#include <stdio.h>

int main(void)
{
	int a = 31;
	int x = 0xFFFFFFFF; /* 一个无符号整型 */

	printf("the first is : %d\n",  0xFFFFFFFF >> 31) ;
												/* 将一个常量右移31位 */
	printf("the second is : %d\n",  x >> 31) ; /* 右移31位，最高的一位变成了
										         最低的一位 */
	printf("the third is : %d\n",  0xFFFFFFFF >> a) ;

	return 0;
}

