#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

/*
void signal_fun1(int signo)
{
	printf("SIGINT signo=%d\n", signo);
}


void signal_fun2(int signo)
{
	printf("SIGQUIT signo=%d\n", signo);
}
*/


void signal_fun(int signo)
{
	return;
	if(signo == SIGINT)
	{
		printf("SIGINT signo=%d\n", signo);
	}
	else if(signo == SIGQUIT)
	{
		printf("SIGQUIT signo=%d\n", signo);
	}

}


int main(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, SIG_DFL);
	signal(SIGINT, signal_fun1);
	signal(SIGINT, signal_fun);
	signal(SIGINT, SIG_DFL);

	//signal(SIGQUIT, SIG_IGN);
	//signal(SIGQUIT, SIG_DFL);
	//signal(SIGQUIT, signal_fun2);
	//signal(SIGQUIT, signal_fun);

	
	while(1);

	return 0;
}
