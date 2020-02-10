#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
void handler(int signo)
{
	switch(signo){
	case SIGUSR1: /* 处理信号SIGUSR1 */
		printf("Parent : catch SIGUSR1\n");
		break;
	case SIGUSR2: /*处理信号SIGUSR2 */
		printf("Child : catch SIGUSR2\n");
		break;
	default: /* 本例中只使用SIGUSR1和SIGUSR2两个信号，所以绝对不可能执行到这里 */
		printf("should not be here\n");
		break;
	}
	return ;
}
int main(void)
{
	pid_t ppid, cpid;
	/* 为两个信号设置信号处理程序 */
	if(signal(SIGUSR1, handler) == SIG_ERR){ /* 设置出错 */
		perror("can’t set handler for SIGUSR1");
		exit(1);
	}
	if(signal(SIGUSR2, handler) == SIG_ERR){ /* 设置出错 */
		perror("can’t set handler for SIGUSR2");
		exit(1);
	}
	ppid = getpid(); /* 得到父进程的进程ID */
	if((cpid = fork()) <0){ /* 创建子进程 */
		perror("fail to fork");
		exit(1);
	}else if(cpid == 0){ /* 子进程 */
		if(kill(ppid, SIGUSR1) == -1){ /* 向父进程发送SIGUSR1信号 */
			perror("fail to send signal");
			exit(1);
		}
		while(1); /* 死循环，等待父进程的信号 */
	}else{ /* 父进程 */
		sleep(1); /* 休眠，保证子进程先运行，并且发送SIGUSR2信号 */
		if(kill(cpid, SIGUSR2) == -1){ /* 向子进程发送SIGUSR2信号 */
			perror("fail to send signal");
			exit(1);
		}
		sleep(1);/*休眠，保证SIGKILL信号后于SIGUSR2发送*/
		printf("kill child\n"); /* 输出提示信息 */
		if(kill(cpid, SIGKILL) == -1){ /* 发送SIGKILL信号杀死子进程 */
			perror("fail to send signal");
			exit(1);
		}
		if(wait(NULL) == -1){ /* 回收子进程状态，避免僵尸进程 */
			perror("fail to wait");
			exit(1);
		}
	}
	return 0;
}
