#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <signal.h>

void print_err(char *estr)
{
	perror(estr);
	exit(-1);
}

int main(void)
{
	int ret = 0;
	//[0]：读文件描述符
	//[1]：写文件描述符
	int pipefd[2] = {0};//用于存放管道的读写文件描述符
	
	ret = pipe(pipefd);
	if(ret == -1) print_err("pipe fail");

	ret = fork();
	if(ret > 0)
	{	
		//signal(SIGPIPE, SIG_IGN);
		//close(pipefd[0]);	
		while(1)
		{
			write(pipefd[1], "hello", 5);				
			sleep(1);
		}
	}
	else if(ret == 0)
	{
		close(pipefd[1]);
		close(pipefd[0]);
		while(1)
		{
			char buf[30] = {0};
			bzero(buf, sizeof(buf));
			read(pipefd[0], buf, sizeof(buf));
			printf("child, recv data:%s\n", buf);
		}	
	}

	return 0;
}


