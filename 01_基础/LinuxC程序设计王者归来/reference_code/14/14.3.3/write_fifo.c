#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#define BUFSZ PIPE_BUF 
int main(void)
{
	int fd ; 
	int n, i ;
	char buf[BUFSZ];
	time_t tp; 
	printf("I am %d\n",getpid());		/*说明进程的ID*/
	if((fd=open("fifo1",O_WRONLY))<0){	/*以写打开一个FIFO1*/
		perror("open");
		exit(1);
	}
	for ( i=0 ; i<10; i++){				/*循环10次向FIFO中写入数据*/
		time(&tp);						/*取系统当前时间*/
		/*使用sprintf 函数向buf中格式化写入进程ID 和时间值*/
		n=sprintf(buf,"write_fifo %d sends %s",getpid(),ctime(&tp));
		printf("Send msg:%s",buf);
		if((write(fd, buf, n+1))<0) {	/*写入到FIFO中*/
			perror("write");
			close(fd);					/* 关闭FIFO文件 */
			exit(1);
		}
		sleep(3);						/*进程睡眠3秒*/
	}
	close(fd);							/* 关闭FIFO文件 */
	exit(0);
}
