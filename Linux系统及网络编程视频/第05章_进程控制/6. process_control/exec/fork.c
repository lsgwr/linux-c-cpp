#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>



int main(int argc, char **argv)
{
	pid_t ret = 0;
	
	ret = fork();
	if(ret > 0)
	{
		sleep(1);
	}
	else if(ret == 0)
	{
		extern char **environ;
		//int execve(const char *filename, char **const argv, char **const envp);
		char *my_argv[] = {"fds", "dsfds", NULL};
		char *my_env[] = {"AA=aaaaa", "BB=bbbbb", NULL};
		execve("./new_pro", my_argv, my_env);
	}
	
	return 0;
}
