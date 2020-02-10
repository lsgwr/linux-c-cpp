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

	//write(fd, &shmid, sizeof(shmid));
}

char buf[300] = {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\
222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222\
ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff2222222222"};

void signal_fun(int signo)
{
	shmdt(shmaddr);
	shmctl(shmid, IPC_RMID, NULL);
	remove("./fifo");
	remove(SHM_FILE);
	
	exit(-1);	
}

int get_peer_PID(void)
{
	int ret = -1;
	int fifofd = -1;

	/* 创建有名管道文件 */
        ret = mkfifo("./fifo", 0664); 
        if(ret == -1 && errno != EEXIST) print_err("mkfifo fail");
	
	/* 以只读方式打开管道 */
	fifofd = open("./fifo", O_RDONLY);
        if(fifofd == -1) print_err("open fifo fail");

	/* 读管道，获取“读共享内存进程”的PID */
        int peer_pid;
        ret = read(fifofd, &peer_pid, sizeof(peer_pid));
        if(ret == -1) print_err("read fifo fail");

	return peer_pid; 
}

int main(void)
{
	int peer_pid = -1;

	/* 给SIGINT信号注册捕获函数，用于删除共享内存、管道、文件等 */
	signal(SIGINT, signal_fun);


	/* 使用有名管道获取读共享内存进程的PID */
	peer_pid = get_peer_PID();
	
	
	/* 创建、或者获取共享内存 */
	create_or_get_shm();
	
	//建立映射
	shmaddr = shmat(shmid, NULL, 0);
	if(shmaddr == (void *)-1) print_err("shmat fail");	
	
	while(1)
	{
		memcpy(shmaddr, buf, sizeof(buf));
		kill(peer_pid, SIGUSR1);
		sleep(1);
		
	}
	
	return 0;
}




