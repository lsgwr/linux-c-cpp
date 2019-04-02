#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <strings.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include "semaphore.h"



#define SHM_FILE "./shmfile"

#define SHM_SIZE 4096

int shmid = -1;
int semid = -1;
void *shmaddr = NULL;	



static void print_err(char *estr)
{
	perror(estr);	
	exit(-1);
}

void create_or_get_shm(void)
{
	int fd = 0;
	key_t key = -1;	

	fd = open(SHM_FILE, O_RDWR|O_CREAT, 0664);
	if(fd == -1) print_err("open fail");
	
	key = ftok(SHM_FILE, 'b');
	if(key == -1) print_err("ftok fail");
	
	shmid = shmget(key, SHM_SIZE, 0664|IPC_CREAT);
	if(shmid == -1) print_err("shmget fail");

	//write(fd, &shmid, sizeof(shmid));
}

char buf[300] = {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222\
ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff2222222222"};

void signal_fun(int signo)
{
	shmdt(shmaddr);
	shmctl(shmid, IPC_RMID, NULL);
	
	del_sem(semid);//删除信号量集合	

	remove("./fifo");
	remove(SHM_FILE);
	
	exit(-1);	
}



int main(void)
{
	int peer_pid = -1;

	/* 给SIGINT信号注册捕获函数，用于删除共享内存、管道、文件等 */
	signal(SIGINT, signal_fun);


	/* 创建、或者获取共享内存 */
	create_or_get_shm();
	
	//创建信号量集合	
	semid = creat_or_get_sem(2);

	/* 初始化信号量集合 */
	int i = 0;
	for(i=0; i<2; i++)
	{		
		//将编号0的信号量初始化为1,其它初始化为0
		if(i == 0) init_sem(semid, i, 1);
		else init_sem(semid, i, 0);
	}
	
	//建立映射
	shmaddr = shmat(shmid, NULL, 0);
	if(shmaddr == (void *)-1) print_err("shmat fail");	
	
	int semnum_buf[1] = {0};//存放信号量的编号
	while(1)
	{	
		//p sem 0
		semnum_buf[0] = 0;
		p_sem(semid, semnum_buf, 1);
		
		/* 向共享内存写数据 */
		memcpy(shmaddr, buf, sizeof(buf));
		sleep(1);
		
		//v sem 1
		semnum_buf[0] = 1;
		v_sem(semid, semnum_buf, 1);
	}
	
	return 0;
}




