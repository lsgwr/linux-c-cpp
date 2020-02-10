#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
/* 信号SIGUSR1的处理函数 */
void sigusr1_handler(int signo)
{
	printf("catch SIGUSR1\n");
}
int main(void)
{
	sigset_t set;
	sigset_t sig_pend;
	sigemptyset(&set);		/* 将信号集置空 */
	sigemptyset(&sig_pend);	/* 将信号集置空 */
	if((signal(SIGUSR1, sigusr1_handler)) == SIG_ERR){ /* 安装信号处理函数 */
		perror("can’t set handler for SIGUSR1");
		exit(1);
	}
	sigaddset(&set, SIGUSR1); /* 添加SIGUSR1信号 */
	if(sigprocmask(SIG_BLOCK, &set, NULL) == -1){ /* 阻塞SIGUSR1信号 */
		perror("fail to set signal-mask");
		exit(1);
	}
	sleep(10); /* 休眠10秒钟，期间接收信号，注意进程休眠后不会被未决的信号唤醒 */
	if(sigpending(&sig_pend) == -1){ /* 得到所有的未决信号集 */
		perror("fail to get pending signal");
		exit(1);
	}
	if(sigismember(&sig_pend, SIGUSR1) == 1) /* 测试是否有SIGUSR1信号是
													未决的 */
		printf("there is a signal, SIGUSR1, is pending\n");
	else{
		perror("fail to test signal-set");
		exit(1);
	}
	if(sigprocmask(SIG_UNBLOCK, &set, NULL) == -1){ /* 取消对SIGUSR1的阻塞，
													    可以处理 */
		perror("fail to set signal-mask");
		exit(1);
	}
	printf("SIGUSR1 is available again\n");
	return 0;
}
