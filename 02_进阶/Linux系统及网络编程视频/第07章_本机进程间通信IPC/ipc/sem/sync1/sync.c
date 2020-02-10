#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include "semaphore.h"



#define NSEMS 3

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
	
	//创建信号量集合
	semid = creat_or_get_sem(NSEMS);

	//初始化信号量集合中的每个信号量
	for(i=0; i<NSEMS; i++)
	{
		if(i == 0) init_sem(semid, i, 1);
		else init_sem(semid, i, 0);
	}

	ret = fork();
	if(ret > 0)
	{
		ret = fork();
		if(ret > 0) //父进程
		{
			while(1)
			{	
				semnum_buf[0] = 2;
				p_sem(semid, semnum_buf, 1);
				printf("333333\n");
				sleep(1);
				semnum_buf[0] = 0;
				v_sem(semid, semnum_buf, 1);
				
			}		
		}
		else if(ret == 0) //子进程2
  		{
			while(1)
			{
				semnum_buf[0] = 1;
				p_sem(semid, semnum_buf, 1);
				printf("222222\n");
				sleep(1);
				semnum_buf[0] = 2;
				v_sem(semid, semnum_buf, 1);
			}		
		}
	}
	else if(ret == 0)//子进程1
	{
		signal(SIGINT, signal_fun);
		while(1)
		{
			semnum_buf[0] = 0;
			p_sem(semid, semnum_buf, 1);
			printf("111111\n");
			sleep(1);
			semnum_buf[0] = 1;
			v_sem(semid, semnum_buf, 1);
		}		
	}
	
	return 0;
}




