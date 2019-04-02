#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

typedef void (*sighandler_t)(int);

void signal_fun1(int signo)
{
//	return;

	printf("SIGINT signo=%d\n", signo);
}

int main(void)
{	
	sighandler_t ret = NULL;
	//void (*ret)(void) =NULL;
	

	ret = signal(SIGINT, SIG_IGN);
	ret = signal(SIGINT, SIG_DFL);
	ret = signal(SIGINT, signal_fun1);
	//ret = signal(SIGINT, SIG_DFL);
	
	if(ret == SIG_ERR)
	{
		perror("signal fail");
	}
	else if(SIG_IGN == ret)
	{
		printf("ignoe\n");
	}
	else if(SIG_DFL == ret)
	{
		printf("default\n");
	}
	else 
	{
		printf("capture: %p\n", ret);
	}
	
	

	while(1);

	return 0;
}
