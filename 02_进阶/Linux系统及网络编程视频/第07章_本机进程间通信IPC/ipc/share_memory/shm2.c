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


#define SHM_FILE "./shmfile"

#define SHM_SIZE 4096

int shmid = -1;
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

void snd_self_PID(void)
{
	int ret = -1;
	int fifofd = -1;

	/* 创建有名管道文件 */
	mkfifo("./fifo", 0664); 
	if(ret == -1 && errno != EEXIST) print_err("mkfifo fail");
	
	/* 以只写方式打开文件 */
	fifofd = open("./fifo", O_WRONLY);
	if(fifofd == -1) print_err("open fifo fail");
	
	/* 获取当前进程的PID, 使用有名管道发送给写共享内存的进程 */
	int pid = getpid();
	ret = write(fifofd, &pid, sizeof(pid));//发送PID
	if(ret == -1) print_err("write fifo fail");
}

int main(void)
{

	/*给SIGUSR1注册一个空捕获函数，用于唤醒pause()函数 */
	signal(SIGUSR1, signal_fun);
	signal(SIGINT, signal_fun);

	/* 使用有名管道，讲当前进程的PID发送给写共享内存的进程 */
	snd_self_PID();	


	/* 创建、或者获取共享内存 */
	create_or_get_shm();


	//建立映射
	shmaddr = shmat(shmid, NULL, 0);
	if(shmaddr == (void *)-1) print_err("shmat fail");	
	
	while(1)
	{
		pause();
		printf("%s\n", (char *)shmaddr);
		bzero(shmaddr, SHM_SIZE);
	}
	
	return 0;
}




