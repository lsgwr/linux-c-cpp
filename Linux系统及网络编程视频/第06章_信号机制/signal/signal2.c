#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

typedef void (*sighandler_t)(int);

void signal_fun1(int signo)
{
	printf("SIGINT signo=%d", signo);
	
	exit(-1);
	//_exit(-1);
}

void process_exit_deal_fun(void)
{
	printf("process over");
	printf("save list to file");
}

int main(void)
{
	//atexit(process_exit_deal_fun);
		
	//signal(SIGINT, signal_fun1);

	//printf("hello");

	printf("SIG_ERR = %d\n", SIG_ERR);
	printf("SIG_IGN = %d\n", SIG_IGN);
	printf("SIG_DFL = %d\n", SIG_DFL);
	
	while(1);

	return 0;
}
