#include <stdio.h>
int main(void)
{
	/* 这个缓冲区已经很大了，如果用户输入是在命令行方式下的话，该缓冲的空间是足够的 */
	char buf[2048]; 
	while(gets(buf) != NULL){ /* 从屏幕读入一行字符串 */
		printf("%s\n", buf); /* 并且将该字符串显示输出到屏幕上 */
	}
	return 0;
}
