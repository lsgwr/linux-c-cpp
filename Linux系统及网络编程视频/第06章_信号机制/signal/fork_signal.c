#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>


void signal_fun(int signo)
{
	printf("PID:%d, signo=%d\n", getpid(), signo);
	
}

int main(int argc, char **argv, char **environ)
{
	pid_t ret = 0;
	
	//signal(SIGINT, SIG_IGN);
	//signal(SIGINT, signal_fun);
	//signal(SIGINT, SIG_DFL);


	ret = fork();
	if(ret > 0)
	{
		signal(SIGINT, signal_fun);
	}
	else if(ret == 0)
	{
		signal(SIGINT, signal_fun);
	}
	
	while(1);
	
	return 0;
}
