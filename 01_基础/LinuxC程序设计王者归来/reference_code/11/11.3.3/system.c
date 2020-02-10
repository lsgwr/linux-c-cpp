#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define MAX 1024
int main(void)
{
	int fd, n;
	char buf[MAX]; /* 保存文件内容的缓冲区 */
	if(system("ls > temp.txt") == -1){ /* 使用system执行ls命令，并将结果输
										出到temp.txt文件中 */
		perror("fail to exec command");
		exit(1);
	}
	if((fd = open("temp.txt", O_RDWR)) == -1){ /* 打开temp.txt文件 */
		perror("fail to open");
		exit(1);
	}
	printf("%d",fd);
	if((n = read(fd, buf, MAX)) == -1){ /* 读文件内容 */
		perror("fail to read");
		exit(1);
	}
	buf[n] = '\0';		/* 添加'\0'结束符 */
	printf("%s", buf);	/* 文件内容中自带'\n' */
	return 0;
}
