#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <semaphore.h>

#define SECON_PTH_NUMS 	2  //次线程数量
#define SEM_NUMS 1 //集合中信号量数量

/* 传递给线程的参数 */
typedef struct pthread_arg 
{
	pthread_t tid;//存放线程tid
	int pthno;//我自己定义的编号
	int fd;//文件描述符
}ptharg;

struct gloable_va
{
	ptharg pth_arg[SECON_PTH_NUMS];//结构体数组,每个元素会被当做参数传递给对应的次线程
	sem_t sem[SEM_NUMS];
	
}glbva;

void print_err(char *str, int line, int err_no)
{
	printf("%d, %s:%s", line, str, strerror(err_no));
	exit(-1);
}

void *pth_fun(void *pth_arg)
{	
	int fd = ((ptharg *)pth_arg)->fd;

	while(1)
	{
		sem_wait(&glbva.sem[0]);
		write(fd, "hello ", 6);
		write(fd, "world\n", 6);
		sem_post(&glbva.sem[0]);
	}

	return NULL;
}

void signal_fun(int signo)
{
	int i = 0;
	int ret = 0;

	for(i=0; i<SEM_NUMS; i++)
	{
		ret = sem_destroy(&glbva.sem[i]);
		if(ret != 0) print_err("sem_destroy fail", __LINE__, ret);
	}
	exit(-1);
}

int main(void)
{
	int fd = 0;
	int i = 0;
	int ret = 0;


	signal(SIGINT, signal_fun);	
	
	//打开文件,供线程操作,所有的线程(函数)可以共享打开的文件描述符
	fd = open("./file", O_RDWR|O_CREAT|O_TRUNC, 0664);
	if(fd == -1) print_err("open ./file fail", __LINE__, errno);
	
	/* 初始化信号量 */
	for(i=0; i<SEM_NUMS; i++)
	{	
		if(i == 0) ret = sem_init(&glbva.sem[i], 0, 1);
		else ret = sem_init(&glbva.sem[i], 0, 0);
		if(ret != 0) print_err("sem_init fail", __LINE__, errno);
	}


	/* 通过循环创建两个次线程 */
	for(i=0; i<SECON_PTH_NUMS; i++)
	{
		glbva.pth_arg[i].fd = fd;//保存文件描述符
		glbva.pth_arg[i].pthno = i; //我自己给的线程编号
						           //创建好次线程后,讲次线程分离
		ret = pthread_create(&glbva.pth_arg[i].tid, NULL, pth_fun, (void *)&glbva.pth_arg[i]);	
		if(ret != 0) print_err("pthread_create fail", __LINE__, ret);
	}

	while(1)
	{	
		sem_wait(&glbva.sem[0]);
		write(fd, "hello ", 6);
		write(fd, "world\n", 6);
		sem_post(&glbva.sem[0]);
	}		
	
	return 0;
}

