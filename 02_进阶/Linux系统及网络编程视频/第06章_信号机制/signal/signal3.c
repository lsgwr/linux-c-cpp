#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void signal_fun1(int signo)
{
	printf("SIGINT signo=%d", signo);
	
	exit(-1);
}

int main(void)
{
	int i = 0;
	
	for(i=0; i<64; i++)
	{
		signal(i, SIG_IGN);
	}

	while(1);

	return 0;
}
