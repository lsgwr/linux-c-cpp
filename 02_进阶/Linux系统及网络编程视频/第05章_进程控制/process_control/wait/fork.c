#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char **argv)
{
	pid_t ret = 0;
	
	ret = fork();
	if(ret > 0)
	{
		int status = 0;

		wait(&status);
		printf("status = %d\n", status);
		if(WIFEXITED(status))
		{
			printf("exited:%d\n", WEXITSTATUS(status));
		}
		else if(WIFSIGNALED(status))
		{
			printf("signal killed:%d\n", WTERMSIG(status));
		}
		
	}
	else if(ret == 0)
	{
		extern char **environ;
		execve("./new_pro", argv, environ);
	}
	
	return 0;
}
