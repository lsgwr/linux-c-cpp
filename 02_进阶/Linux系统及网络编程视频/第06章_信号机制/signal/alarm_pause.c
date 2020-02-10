#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>


void signal_fun1(int signo)
{
	printf("time up\n");
}

void signal_fun2(int signo)
{
}


int main(int argc, char **argv, char **environ)
{
	unsigned int ret = 0;	
	
	/*
	signal(SIGALRM, signal_fun);
	ret = alarm(5);
	sleep(6);
	ret = alarm(6);
	printf("ret = %d\n", ret);	
	*/
	
	signal(SIGINT, signal_fun2);

	pause();
	printf("hello\n");

	while(1);
	
	return 0;
}
