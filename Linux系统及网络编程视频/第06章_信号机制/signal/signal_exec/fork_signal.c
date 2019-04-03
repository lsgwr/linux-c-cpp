#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void signal_fun(int signo)
{
	printf("parent PID:%d, signo=%d\n", getpid(), signo);
}

int main(int argc, char **argv, char **environ)
{
	pid_t ret = 0;
	
	//signal(SIGINT, SIG_IGN); // "忽略"会被子进程继承
	//signal(SIGINT, SIG_DFL); // "默认"会被子进程继承
	signal(SIGINT, signal_fun); // "捕获"会被子进程覆盖为"默认"

	ret = fork();
	if(ret > 0)
	{
	}
	else if(ret == 0)
	{
		// 当有调用exec加载新程序时, 信号的处理方式会被还原为默认处理方式
		execve("./new_pro", argv, environ);
	}
	
	while(1);
	
	return 0;
}
