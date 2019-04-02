#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include "semaphore.h"



#define NSEMS 1

int semid;


void signal_fun(int signo)
{
	del_sem(semid, NSEMS);
	exit(-1);
}

int main(void)
{
	int i = 0;
	int ret = 0;
	int fd = -1;
	int semnum_buf[1] = {0};
	
	fd = open("./file", O_RDWR|O_CREAT|O_TRUNC, 0664);
	if(fd == -1) print_err("open file fail");

	semid = creat_or_get_sem(NSEMS);
	
	for(i=0; i<NSEMS; i++)
	{
		init_sem(semid, i, 1);
	}

	ret = fork();
	if(ret > 0)
	{
		signal(SIGINT, signal_fun);
		while(1)
		{
			semnum_buf[0] = 0;//设置要操作的信号量的编号
			p_sem(semid, semnum_buf, 1); //P操作
			write(fd, "hello ", 6);
			write(fd, "world\n", 6);
			semnum_buf[0] = 0; //设置要操作的信号量的编号
			v_sem(semid, semnum_buf, 1);//v操作
		}		
	}
	else if(ret == 0)
	{
		while(1)
		{
			semnum_buf[0] = 0;//设置要操作的信号量的编号
			p_sem(semid, semnum_buf, 1); //P操作
			write(fd, "hhhhh ", 6);
			write(fd, "wwwww\n", 6);
			semnum_buf[0] = 0; //设置要操作的信号量的编号
			v_sem(semid, semnum_buf, 1);//v操作
		}		
	}

	return 0;
}




