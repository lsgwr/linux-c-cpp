#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>


int main(int argc, char **argv, char **environ)
{
	//kill(getpid(), SIGUSR1);
	//kill(63931, SIGTERM);
	raise(SIGABRT);

	abort();
	
	while(1);
	
	return 0;
}
