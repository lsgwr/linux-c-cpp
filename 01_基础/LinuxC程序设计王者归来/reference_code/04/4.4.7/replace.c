#include <stdio.h>

/* 替换函数将参数p中出现的所有空格替换为‘_’
* 如果成功替换返回最后一个空格字符出现的地址，失败返回NULL
*/
const char * replace(const char *str)	/* 严格地使用const关键字修饰变量 */
{
	const char *p;						/* 严格地使用const关键字修饰变量 */

	if(str == NULL)
		return NULL;

	p = str;
	while(*p != '\0'){ /* 遍历每一个字符，将检查到的空格字符替换为‘_’ */
		/* 这一步操作会由编译器发现程序尝试写只读数据段。
		*因为和源字符串相关的指针已经被声明为了指向const变量的指针
		*/
		if(*p == ' ')
			*p = '_';
		p++;
	}

	return p; /* 返回最后一个空格出现的位置 */
}

int main(void)
{
	const char *p = "hello world and China\n"; /* 使用const将源字符串指针声
												   明为const变量 */

	if(replace(p) != NULL) /* 调用replace函数将空格替换 */
		printf("the string : %s",p);

	return 0;
}
