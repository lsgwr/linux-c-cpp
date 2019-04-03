#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>


void signal_fun(int signo)
{
	printf("new_pro pid:%d, signo=%d\n", getpid(), signo);	
}

int main(void)
{

	// 新程序的代码会覆盖子进程中原有的父进程的代码，信号捕获函数的代码也会被覆盖
    // 既然捕获函数已经不存在了，捕获处理方式自然也就没有意义了，所以信号的处理方式会被还原为默认处理方式
	signal(SIGINT, signal_fun);
	while(1);

	return 0;
}




