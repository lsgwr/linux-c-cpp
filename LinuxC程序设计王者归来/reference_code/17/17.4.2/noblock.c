#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#define MAX 100000
#define LEN 1024  /* 使用宏作为缓冲区的大小 */
int main(int argc, char *argv[ ])
{
	int fd1, fd2; 
	FILE *fp;
	char buf[MAX];     /* 大文件的缓冲区 */
	int n, rest;
	char *p = buf;
	char content[LEN];
	if(argc != 3){ /* 缺少文件名 */
		printf("expect args\n");
		exit(1);
	}
	fd1 = open(argv[1], O_RDONLY); 		/* 输入文件 */
	if(fd1 == -1){
		perror("fail to read");
		exit(1);
	}
	fp = fopen(argv[2], "w"); 			/* 输出错误原因的文件，使用格式化I/O */
	if(fp == NULL){
		perror("fail to read");
		exit(1);
	}
	fd2 = open("test.txt", O_WRONLY);	/* 输出文件，低速文件test.txt文件 */
	if(fd2 == -1){
		perror("fail to read");
		exit(1);
	}
	rest = read(fd1, buf, MAX); 		/* 读文件的内容到缓冲区 */
	printf("get %d bytes from %s\n", rest, argv[1]);
	while(rest > 0){ /* 当要输出的内容还有剩余时继续输出 */
		errno = 0;
		n = write(fd2, p, rest); 		/* 输出缓冲区内容 */
		fprintf(fp, "write %d, errno %s\n", n, strerror(errno));
										/* 如果输出失败则输出错误原因 */
		if(rest > 0){ /* 计算剩余的字节数 */
			p += n;
			rest -= n;
		}
	}
	printf("done\n");
	return 0;
}
