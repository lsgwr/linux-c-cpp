#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024

int output(char *file_name)
{
	FILE *fp;
	char buf[MAX];	
	int n;
	static int count = 0;		/* 静态局部变量，保存输出的行数 */

	fp = fopen(file_name, "r");	/* 打开文件 */
	if(fp == NULL){
		perror("fail to open");	/* 输出则提示 */
		return -1;		
	}
	
	while(fgets(buf,MAX,fp) != NULL){ /* 每次读入文件的一行 */
		n = strlen(buf);
		buf[n - 1] = '\0';

		printf("%s\n", buf); /* 输出读入的一行 */

		if(count++ % 5 == 0) /* 累加count，如果count能够被5整除，则输出换行 */
			printf("\n");
	}

	fclose(fp);			    /* 关闭文件 */
	
	return 0;
}

int main(void)
{
	char file_name[][10] = {"text.txt", 
					"text1.txt",
					"text2.txt"
					};
	int i;
	
	i = 0;
	while(i < 3){
		if(output(file_name[i]) == -1) /* 输出每一个文件中的内容 */
			exit(1);
		i++;
	}

	return 0;
}

