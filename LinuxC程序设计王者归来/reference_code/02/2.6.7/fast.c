#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1024

void lower2(char *p)
{	
	int i, len;
	
	len = strlen(p);				/* 将字符串长度的计算提到循环外进行 */
	for(i = 0; i < len; i++)		/* 将字符串中的大写字母转换为小写 */
		if(p[i] >= 'A' && p[i] <= 'Z')
			p[i] += 32;				/* 将大写字母转换为小写 */
	printf("%s",p);
}

int main(void)
{
	FILE *fp;
	char buf[MAX];						/* 存放文件内容的缓冲区 */
	int n;
	fp = fopen("text.txt", "r");	/* 打开一个文件 */
	if(fp == NULL){
		perror("fail to open");
		exit(1);
	}

	while((n = fread(buf, sizeof(char), MAX - 1, fp)) > 0){ /* 循环读入文件
													  的内容，直到文件结束 */
		buf[n] = '\0';
		lower2(buf);
	}

	if(n < 0){						/* 读入文件失败 */
		perror("fail to read");
		exit(1);
	}

	fclose(fp); 					/* 关闭文件 */

	return 0;
}

