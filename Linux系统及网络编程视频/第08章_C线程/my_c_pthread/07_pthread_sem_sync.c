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
#define SEM_NUMS (SECON_PTH_NUMS + 1) //集合中信号量数量

#define print_error_thread(str, errno) \
do{\
    fprintf(stderr, "File %s, Line %d, Function %s error\n",__FILE__, __LINE__, __func__);\
    printf("%s:%s", str, strerror(errno));\
    exit(-1);\
}while(0);

#define print_error(str) \
do{\
    fprintf(stderr, "File %s, Line %d, Function %s error\n",__FILE__, __LINE__, __func__);\
    perror(str);\
    exit(-1);\
}while(0);

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

void *pth_fun1(void *pth_arg)
{	
	while(1){
		sem_wait(&glbva.sem[0]);
		printf("111111\n");
		sleep(1);
		sem_post(&glbva.sem[1]);
	}

	return NULL;
}

void *pth_fun2(void *pth_arg)
{	
	while(1){
		sem_wait(&glbva.sem[1]);
		printf("222222\n");
		sleep(1);
		sem_post(&glbva.sem[2]);
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
		if(ret != 0) print_error("sem_destroy fail");
	}
	exit(-1);
}

int main(void)
{
	int i = 0;
	int ret = 0;
	void *(*pth_fun_buf[])(void *) = {pth_fun1, pth_fun2};

	signal(SIGINT, signal_fun);	

	/* 初始化信号量 */
	for(i=0; i<SEM_NUMS; i++)
	{	
		if(i == 0) ret = sem_init(&glbva.sem[i], 0, 1);
		else ret = sem_init(&glbva.sem[i], 0, 0);
		if(ret != 0) print_error("sem_init fail");
	}


	/* 通过循环创建两个次线程 */
	for(i=0; i<SECON_PTH_NUMS; i++)
	{
		ret = pthread_create(&glbva.pth_arg[i].tid, NULL, pth_fun_buf[i], NULL);
		if(ret != 0) print_error_thread("pthread_create fail", ret);
	}

	while(1){
		sem_wait(&glbva.sem[2]);
		printf("333333\n");	
		sleep(1);
		sem_post(&glbva.sem[0]);
	}		
	
	return 0;
}

