#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>


#define FIFONAME1 "./fifo1"
#define FIFONAME2 "./fifo2"

void print_err(char *estr)
{	
	perror(estr);
	exit(-1);
}	

int creat_open_fifo(char *fifoname, int open_mode)
{	
	int ret = -1;
	int fd = -1;	
	
	ret = mkfifo(fifoname, 0664);
	//如果mkfifo函数出错了，但是这个错误是EEXIST，不报这个错误（忽略错误）
	if(ret == -1 && errno!=EEXIST) print_err("mkfifo fail");	
	
	fd = open(fifoname, open_mode);
	if(fd == -1) print_err("open fail");

	return fd;
}

void signal_fun(int signo)
{
	//unlink();
	remove(FIFONAME1);
	remove(FIFONAME2);
	exit(-1);
}
		
int main(void)
{
	char buf[100] = {0};
	int ret = -1;
	int fd1 = -1;
	int fd2 = -1;


	fd1 = creat_open_fifo(FIFONAME1, O_WRONLY);
	fd2 = creat_open_fifo(FIFONAME2, O_RDONLY);

	ret = fork();
	if(ret > 0)
	{
		signal(SIGINT, signal_fun);
		while(1)
		{
			bzero(buf, sizeof(buf));
			scanf("%s", buf);
			write(fd1, buf, sizeof(buf));	
		}
	}
	else if(ret == 0)
	{
		while(1)
		{
			bzero(buf, sizeof(buf));
			read(fd2, buf, sizeof(buf));
			printf("%s\n", buf);
		}
	}

	return 0;
}	
	



	
	
	
