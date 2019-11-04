#include <stdio.h>

int main(void)
{
	char *str1 = "hello";		/* 字符串 */
	char str2[] = "hello";		/* 字符数组 */
	char *str3 = "hello";		/* 字符串 */

	if(str1 == str2)			/* 比较指针str1和数组名str2 */
		printf("1 OK\n");
	if(str1 == str3)			/* 比较指针str1和指针str3 */
		printf("2 OK\n");

	return 0;
}
