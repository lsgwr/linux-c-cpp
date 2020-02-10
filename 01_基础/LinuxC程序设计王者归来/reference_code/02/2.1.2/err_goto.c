#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
/* 转换函数，如果成功则返回0，失败返回-1 */
int convert(void)
{
	FILE *fp;
	struct stat statbuf;	/* 文件状态的存储结构 */
	char *p, *q;
	int n;
	int res = -1;		/* 函数的返回值 */

	if(stat("text.txt", &statbuf) == -1){ /* 得到文件状态，得到文件的大小 */
		perror("fail to get stat");
		return res;
	}

	fp = fopen("text.txt", "rb"); /* 打开文件失败，还没有分配到资源，直接退出 */
	if(fp == NULL){
		perror("fail to open");
		return res;
	}
	
	/* 动态分配保存文件内容的缓冲区，如果失败需要关闭上一个fopen打开的文件，跳转到
	err1 */
	p = (char *)malloc(sizeof(char) * (statbuf.st_size + 1));
	if(p == NULL){
		perror("fail to malloc");
		goto err1;
	}
	
	/* 读取文件内容，如果失败，则需要释放动态分配的缓冲区，并且关闭打开的文件，跳转到
	err2 */
	n = fread(p, sizeof(char), statbuf.st_size, fp);
	if(n == -1){ /* 当输出字符数等于-1的时候，程序出错 */
		perror("fail to read");
		goto err2;
	}
	*(p + n) = '\0'; /* 设置结束标志'v\0' */
	
	q = p;
	while(*q != '\0'){ /* 处理文件内容，将小写字符转换为大写字符输出 */
		if('a' >= *q && *q <= 'z')
			*q += 32; /* 大小写进行转换 */
		printf("%c",*q);
		q++;
	}
	
	res = 0; /* 执行到此，一切正常，返回0 */
err2:
	free(p);				/* 释放动态分配的缓冲区 */
err1:
	fclose(fp);				/* 关闭打开的文件 */

	return res;
}

int main(void)
{
	if(convert( ) == -1)	/* 调用convert函数，如果出错则输出出错信息 */
		printf("fail to convert\n");

	return 0;
}

