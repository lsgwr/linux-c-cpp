#include <stdio.h>
#include <stdlib.h>
#include <string.h>
my_print (char *string)
{
	printf ("The string is %s\n", string); /* 输出一个字符串 */
}
void my_print2 (char *string)
{
	char *string2;
	int size,size2,i;
	size = strlen (string);
	size2=size-1;
	string2 = (char *) malloc (size + 1); /* 为string2分配存储空间 */
	for (i = 0; i < size; i++)	/* 将字符串string的内容复制到string2中 */
		string2[size2-i] = string[i];
	string2[size] = '\0';				/* 添加'\0'结束符 */
	printf ("The string printed backward is %s\n", string2); /* 输出字符串 */
}
int main (void)
{
	char my_string[] = "hello there";	    /* 第一个字符串 */
	my_print (my_string);				    /* 调用两个函数 */
	my_print2 (my_string);
	return 0;
}
