#include <stdio.h>
#include <string.h>
/* 合并两个字符串的函数
* str1 : 需要合并的第一个字符串
* str2 : 需要合并的第二个字符串
*/
char * combine(char * str1, char * str2)
{
	char str[1024];
	char *p = str;
	strcpy(str, str1);	/* 复制第一个字符串 */
	strcat(str, str2);	/* 将第二个字符串连接到第一个字符串的末尾 */
	return p;			/* 返回合并好的串的首地址 */
}
int main(void)
{
	char *p;
	p = combine("hello", "world");	/* 调用combine函数 */
	printf("%s\n", *p);				/* 输出调用结果 */
	return 0;
}
