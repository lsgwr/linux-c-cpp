#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFSZ PIPE_BUF
int main(void)
{
	int fd;
	int len;
	char buf[BUFSZ];
	mode_t mode = 0666;					/* FIFO文件的权限 */
	if((fd=open("fifo1",O_RDONLY))<0)	/* 打开FIFO文件 */
	{
		perror("open");
		exit(1);
	}
	while((len=read(fd,buf, BUFSZ))>0)	/* 开始进行通信 */
		printf("read_fifo read: %s",buf);
	close(fd); /* 关闭FIFO文件 */
	exit(0);
}
