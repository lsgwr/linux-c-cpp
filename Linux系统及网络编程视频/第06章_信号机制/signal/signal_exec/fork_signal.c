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
	
	//signal(SIGINT, SIG_IGN);
	signal(SIGINT, signal_fun);
	//signal(SIGINT, SIG_DFL);

	ret = fork();
	if(ret > 0)
	{
	}
	else if(ret == 0)
	{
		execve("./new_pro", argv, environ);
	}
	
	while(1);
	
	return 0;
}
