#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1024

void lower1(char *p) 				/* 大小写转换函数 */
{	
	int i;

	for(i = 0; i < strlen(p); i++)	/* 将字符串中的大写字母转换为小写 */
		if(p[i] >= 'A' && p[i] <= 'Z')
			p[i] += 32;				/* 转换为小写字母 */
	printf("%s",p);
		
}

int main(void)
{
	FILE *fp;
	char buf[MAX];
	int n;
	fp = fopen("text.txt", "r");	/* 打开文件 */
	if(fp == NULL){
		perror("fail to open");
		exit(1);
	}

	while((n = fread(buf, sizeof(char), MAX - 1, fp)) > 0){ /* 读取一个字符
																串。直到文件
																结束 */
		buf[n] = '\0';
		lower1(buf);
	}

	if(n < 0){						/* 读入文件出错 */
		perror("fail to read");
		exit(1);
	}

	fclose(fp);						/* 关闭文件 */

	return 0;
}

