#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
/* SIGALRM的处理函数 */
void timer_handler(int signo)
{
	if(signo == SIGALRM){				/* 捕捉SIGALRM信号 */
		printf("the time is now\n");	/* 捕捉后打印提示信息 */
		exit(0); /* 之后退出，注意不会返回到捕捉信号前程序的断点，直接退出程序 */
	}else
		printf("unexpected signal\n");	/* 不应该执行到这里 */
}
int main(void)
{
	if(signal(SIGALRM, timer_handler) == SIG_ERR){ /* 设置SIGALRM的信号处理程序 */
		perror("can’t set handler for SIGALRM");
		exit(0);
	}
	alarm(1);								/* 设置定时器，定时时间为1秒 */
	while(1)
		printf("too early\n");				/* 在定时器到时之前打印提示信息 */
	printf("should not be here, never\n");	/* 不应该执行到这里 */
	return 0;
}
