#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define MAX 1024
#define PID 6
#define PATH_SIZE 128
int main(void)
{
	FILE *fp;
	pid_t pid;
	char pid_str[PID];
	char path[PATH_SIZE];
	char buf[MAX];
	pid = getpid(); 					/* 得到进程ID */
	sprintf(pid_str, "%d", pid); 		/* 将进程ID由数字转换为字符串 */
	strcpy(path, "/proc/self/task/");	/* 拼接路径，打开"/proc/self/task/进
										程ID"目录下的status文件 */
	strcat(path, pid_str);
	strcat(path, "/status");
	fp = fopen(path, "r"); 				/* 打开该文件，以只读的方式打开 */
	if(fp == NULL){
		perror("fail to open");
		exit(1);
	}
	while(fgets(buf, MAX, fp) != NULL)	/* 顺序读取每一行，并且打印 */
		printf("%s", buf);
	fclose(fp); /* 关闭文件 */
	return 0;
}
