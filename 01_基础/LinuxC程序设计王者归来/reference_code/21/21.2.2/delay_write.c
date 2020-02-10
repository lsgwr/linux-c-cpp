#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	FILE *fp;
	int i;	
	fp = fopen("test.txt", "wb"); /* 打开一个文件 */
	if(fp == NULL){
		perror("fail to open");
		exit(1);
	}
	i = 0;
	while(i < 5){	/* 每隔3秒钟向文件输出一行字符 */
		fprintf(fp, "hello world\n");
		sleep(3);	/* 休眠3秒钟，便于用户检查试验结果 */
		i++;
	}
	fclose(fp);		/* 关闭文件，会将文件内容"冲洗"到磁盘上 */
	return 0;
}
