#include <stdio.h>

int main(void)
{
	char ch[] = {'h', 'e', 'l', 'l', 'o', '\0'};	/* 字符串初始化 */
		
	printf("%s\n", ch);								/* 输出字符串 */

	ch[3] = '\0'; /* 将字符数组的第4个元素更改为结束符，字符串提前结束 */
	printf("%s\n", ch);
	
	return 0;
}
