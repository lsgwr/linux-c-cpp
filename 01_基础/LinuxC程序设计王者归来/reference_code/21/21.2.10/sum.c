#include <stdio.h>
#include <stdlib.h>
#define MAX 1024
int main(void)
{
	FILE *fp;
	char buf[MAX];
	int n;
	char *p;
	int letter, number, blank;
	fp = fopen("test.txt", "rb"); /* 打开该文件 */
	if(fp == NULL){
		perror("fail to open");
		exit(1);
	}
	letter = 0;
	number = 0;
	blank = 0;
	/* 循环读取文件的内容，该文件可能很大，不能一次读入到缓冲区中 */
	while((n = fread(buf, sizeof(char), MAX - 1, fp)) > 0){
		buf[n] = '\0'; /* 手动设置结束符 */
		p = buf;
		while(*p != '\0'){ /* 处理每次读入的文件内容 */
			if(('a' <= *p && *p <= 'z') || ('A' <= *p && *p <= 'Z')) 
													/* 判断为字母 */
				letter++;
			if(*p == ' ') 							/* 判断为空格 */
				blank++;
			if('0' <= *p && *p <= '9') 				/* 判断为数字 */
				number++;
			p++;
		}
	}
	if(n == -1){ /* 读操作出错 */
		perror("fail to read");
		exit(1);
	}
	/* 输出结果，字母数、数字数和空格数 */
	printf("the sum of letter is : %d\nthe sum of number is : %d\nthe sum of blank is : %d\n", letter, number, blank);
	return 0;
}

