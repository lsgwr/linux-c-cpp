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



void print_err(char *estr)
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
	
	//read(fd, &shmid, sizeof(shmid));
}

void signal_fun(int signo)
{
	if(SIGINT == signo)
	{
		shmdt(shmaddr);
		shmctl(shmid, IPC_RMID, NULL);
		remove("./fifo");
		remove(SHM_FILE);

		exit(-1);
	}
	else if(SIGUSR1 == signo)
	{
		
	}
}

int main(void)
{
	signal(SIGINT, signal_fun);

	/* 创建、或者获取共享内存 */
	create_or_get_shm();
	
	//获取别人创建号的信号量
	semid = creat_or_get_sem(2);

	//建立映射
	shmaddr = shmat(shmid, NULL, 0);
	if(shmaddr == (void *)-1) print_err("shmat fail");	

	int semnum_buf[1] = {0};//存放信号量编号	
	while(1)
	{
		//p sem 1
		semnum_buf[0] = 1;
                p_sem(semid, semnum_buf, 1);

		//从共享内存去除数据并打印显示
		printf("%s\n", (char *)shmaddr);
		bzero(shmaddr, SHM_SIZE);//清空共享内存
		
		//v sem 0
                semnum_buf[0] = 0;
                v_sem(semid, semnum_buf, 1);
	}
	
	return 0;
}




