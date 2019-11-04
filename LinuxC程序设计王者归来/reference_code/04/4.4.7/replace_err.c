#include <stdio.h>

/* 替换函数将参数p中出现的所有空格替换为‘_’
* 如果成功替换返回最后一个空格字符出现的地址，失败返回NULL
*/
char * replace(char *str)
{
	char *p;

	if(str == NULL) /* 与字符串为空则退出 */
		return NULL;

	p = str;
	while(*p != '\0'){ /* 遍历每一个字符，将检查到的空格字符替换为‘_’ */
		if(*p == ' ')
			*p = '_'; /* 进行字符的替代 */
		p++;
	}

	return p; 								/* 返回最后一个空格出现的位置 */
}
int main(void)
{
	char *p = "hello world and China\n";	/* 需要替代的字符串 */

	if(replace(p) != NULL)					/* 调用replace函数将空格替换 */
		printf("the string : %s",p);

	return 0;
}
