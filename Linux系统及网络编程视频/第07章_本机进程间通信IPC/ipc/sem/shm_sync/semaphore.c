#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun 
{
	int val;   
	struct semid_ds *buf;    
	unsigned short  *array;  /* 不做要求 */
	struct seminfo  *__buf;  /* 不做要求 */
};

#define SEM_FILE "./semfile"

static void print_err(char *estr)
{
        perror(estr);
        //exit(-1);
}

int creat_or_get_sem(int nsems)
{
	int semid;
	int fd = -1;
	key_t key = -1;

	fd = open(SEM_FILE, O_RDWR|O_CREAT, 0664);
	if(fd == -1) print_err("open ./semfile fail");
	
	key = ftok(SEM_FILE, 'a');	
	if(key == -1) print_err("ftok fail");

	semid = semget(key, nsems, 0664|IPC_CREAT);
	if(semid == -1) print_err("semget fail");

	return semid;	
}

void init_sem(int semid, int semnum, int val)
{
	int ret = -1;
	union semun sem_un;

	/* semnum:信号量编号
	 * SETVAL:设置信号量初始值cmd
	 * sem_un:初始值
	 */	
	sem_un.val = val;
	ret = semctl(semid, semnum, SETVAL, sem_un);
	if(ret == -1) print_err("semctl fail");
}


void del_sem(int semid)
{
	int ret = 0;

	ret = semctl(semid, 0, IPC_RMID);
	if(ret == -1) print_err("semctl del sem fail");

	remove(SEM_FILE);
}

void p_sem(int semid, int semnum_buf[], int nsops)
{
	int i = 0;
	int ret = -1;
	struct sembuf sops[nsops];
	
	for(i=0; i<nsops; i++)
	{
		sops[i].sem_num = semnum_buf[i];//信号量编号
		sops[i].sem_op 	= -1;//-1 p操作
		sops[i].sem_flg = SEM_UNDO;//防止死锁 
	}

	ret = semop(semid, sops, nsops);
	if(ret == -1) print_err("semop p fail");
}


void v_sem(int semid, int semnum_buf[], int nsops)
{
	int i = 0;
	int ret = -1;
	struct sembuf sops[nsops];
	
	for(i=0; i<nsops; i++)
	{
		sops[i].sem_num = semnum_buf[i];//信号量编号
		sops[i].sem_op 	= 1;//+1 v操作
		sops[i].sem_flg = SEM_UNDO;//防止死锁 
	}

	ret = semop(semid, sops, nsops);
	if(ret == -1) print_err("semop p fail");
}


