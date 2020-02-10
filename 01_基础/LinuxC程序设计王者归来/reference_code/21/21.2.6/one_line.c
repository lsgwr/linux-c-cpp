#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 1024
int main(void)
{
	char buf[MAX_LINE]; /* 缓冲区 */
	FILE *fp;
	int len;
	if((fp = fopen("test.txt", "r")) == NULL){ /* 打开文件 */
		perror("fail to read");
		exit(1);
	}
	while(fgets(buf, MAX_LINE, fp) != NULL){ /* 每次读入一行 */
		len = strlen(buf);
		/* 输出所读到的字符画串，并将字符个数输出 */
		buf[len - 1]='\0'; /* 去掉换行符，这样其他的字符串函数就可以处理了 */
		printf("%s %d\n", buf,len - 1); /* 使用printf函数输出 */
	}
	return 0;
}
