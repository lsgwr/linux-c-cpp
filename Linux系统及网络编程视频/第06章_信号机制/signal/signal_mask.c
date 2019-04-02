#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>


void signal_fun(int signo)
{
	sigset_t set, oldset;
	
	printf("hello\n");
	
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigprocmask(SIG_UNBLOCK, &set, NULL);

	sleep(3);
	
	printf("world\n");	
}

int main(int argc, char **argv, char **environ)
{
	pid_t ret = 0;
	
	signal(SIGINT, signal_fun);

	
	while(1);
	
	return 0;
}
