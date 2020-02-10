#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main(void)
{
	int fd;
	int flag;
	char *p = "1st linux"; 			   /* 测试使用的字符串 */
	char *q = "2nd linux";
	fd = open("test.txt", O_WRONLY); /* 该文件只写打开 */
	if(fd == -1){
		perror("fail to open");
		exit(1);
	}
	if(write(fd, p, strlen(p)) == -1){ /* 输入新内容，该内容会覆盖部分旧的内容 */
		perror("fail to write");
		exit(1);
	}
	flag = fcntl(fd, F_GETFL, 0);	/* 先使用F_GETFL命令得到文件状态标志 */
	if(flag == -1){
		perror("fail to fcntl");
		exit(1);
	}
	flag |= O_APPEND;				/* 将文件状态标志添加“追加写”选项 */
	if(fcntl(fd, F_SETFL, flag) == -1){ /* 将文件状态修改为追加写 */
		perror("fail to fcntl");
		exit(1);
	}
	if(write(fd, q, strlen(q)) == -1){ /* 再次输入新内容，该内容会追加在旧内容
										   的后面 */
		perror("fail to write");
		exit(1);
	}
	close(fd); /* 关闭文件 */
	return 0;
}
