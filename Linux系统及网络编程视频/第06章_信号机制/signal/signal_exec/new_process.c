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

	signal(SIGINT, signal_fun);

	while(1);
	
	return 0;
}




