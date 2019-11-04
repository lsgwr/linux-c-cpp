#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
/* 信号SIGUSR1的处理函数 */
void sigusr1_handler(int signo)
{
	printf("catch SIGUSR1\n");		/* 输出提示信息，提示接收到SIGUSR1信号 */
}
int main(void)
{
	sigset_t set;					/* 信号集 */
	if(signal(SIGUSR1, sigusr1_handler) == SIG_ERR){ /* 设置信号处理函数 */
		perror("can’t set handler for SIGUSR1");
		exit(1);
	}
	sigemptyset(&set);				/* 清空信号集 */
	sigaddset(&set, SIGUSR1);	/* 设置SIGUSR1 */
	if(sigprocmask(SIG_BLOCK, &set, NULL) == -1){ /* 屏蔽该信号，与原屏蔽字做
													 “或”操作 */
		perror("fail to set signal-mask");
		exit(1);
	}
	
	printf("SIGUSR1 is not available\n");			/* 输出提示信息 */
	sleep(10); /* 休眠，等待用户发送SIGUSR1信号 */
	/* 恢复屏蔽的信号，与原屏蔽字做“取反”后“与”操作 */
	if(sigprocmask(SIG_UNBLOCK, &set, NULL) == -1){ 
		perror("fail to set signal-mask");
		exit(1);
	}
	printf("SIGUSR1 is available now\n");	/* 输出提示信息 */
	sleep(10);								/* 再次休眠，等待信号 */
	return 0;
}
