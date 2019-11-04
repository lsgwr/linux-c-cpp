#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#define MAX 100000
#define LEN 1024
int main(int argc, char *argv[ ])
{
	int fd1, fd2; 
	FILE *fp;
	int flags;
	char buf[MAX]; /* 大文件的缓冲区 */
	int n, rest;
	char *p = buf;
	char content[LEN];
	if(argc != 3){ /* 缺少文件名 */
		printf("expect args\n");
		exit(1);
	}
	fd1 = open(argv[1], O_RDONLY); /* 打开输入文件 */
	if(fd1 == -1){
		perror("fail to read");
		exit(1);
	}
	fd2 = open(argv[2], O_WRONLY); /* 打开输出出错信息的文件 */
	if(fd2 == -1){
		perror("fail to read");
		exit(1);
	}
	fp = fdopen(fd2, "w");		/* 打开文件，以只写的方式 */
	if(fp == NULL){
		perror("fail to open");
		exit(1);
	}
	flags = fcntl(STDOUT_FILENO, F_GETFL, 0); /* 将标准输出设置为非阻塞形式 */
	if(flags == -1){
		perror("fail to fcntl");
		exit(1);
	}
	flags |= O_NONBLOCK;					/* 设置非阻塞标志 */
	if(fcntl(STDOUT_FILENO, F_SETFL, 0) == -1){ /* 重新设置文件的状态标志 */
		perror("fail to fcntl");
		exit(1);
	}
	rest = read(fd1, buf, MAX); /* 读入文件 */
	printf("get %d bytes from %s\n", rest, argv[1]);
	while(rest > 0){ /* 当要输出的内容还有剩余时继续输出 */
		errno = 0;
		n = write(STDOUT_FILENO, p, rest); /* 输出缓冲区内容 */
		
		fprintf(fp, "write %d, errno %s\n" ,n, strerror(errno)); 
					/* 如果输出失败则输出错误原因 */
		if(rest > 0){ /* 计算剩余的字节数 */
			p += n;
			rest -= n;
		}
	}
	printf("done\n");
	close(fd1); /* 关闭文件 */
	fclose(fp);
	return 0;
}
