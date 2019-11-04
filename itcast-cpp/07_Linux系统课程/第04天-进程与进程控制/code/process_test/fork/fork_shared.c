#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int a = 100;            //.data 

int main(void)
{
	pid_t pid;
	pid = fork();

	if(pid == 0){	//son
		a = 2000;
		printf("child, a = %d\n", a);
	} else {
		sleep(1);	//保证son先运行
		printf("parent, a = %d\n", a);
	}

	return 0;
}
