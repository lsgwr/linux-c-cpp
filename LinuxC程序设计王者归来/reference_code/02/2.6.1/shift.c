#include <stdio.h>

int main(void)
{
	int a = 12;

	printf("a divided by 4 : %d\n", a >> 2);	    /* 使用右移操作代替除法 */
	printf("a multiplied by 5 : %d\n", (a << 2) + a);/* 使用左移操作代替乘法 */

	return 0;
}

