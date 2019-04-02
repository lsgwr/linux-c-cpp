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
	int pipefd1[2] = {0};//用于存放管道的读写文件描述符
	int pipefd2[2] = {0};//用于存放管道的读写文件描述符
	
	ret = pipe(pipefd1);
	if(ret == -1) print_err("pipe fail");
	ret = pipe(pipefd2);
	if(ret == -1) print_err("pipe fail");

	ret = fork();
	if(ret > 0)
	{	
		close(pipefd1[0]);
		close(pipefd2[1]);
		char buf[30] = {0};
		while(1)
		{
			write(pipefd1[1], "hello", 5);				
			sleep(1);

			bzero(buf, sizeof(buf));
			read(pipefd2[0], buf, sizeof(buf));
			printf("parent, recv data:%s\n", buf);
		}
	}
	else if(ret == 0)
	{
		close(pipefd1[1]);
		close(pipefd2[0]);
		char buf[30] = {0};
		while(1)
		{
			sleep(1);	
			write(pipefd2[1], "world", 5);

			bzero(buf, sizeof(buf));
			read(pipefd1[0], buf, sizeof(buf));
			printf("child, recv data:%s\n", buf);
		}	
	}

	return 0;
}


