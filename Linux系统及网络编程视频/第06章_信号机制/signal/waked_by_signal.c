#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

void signal_fun(int signo)
{
	printf("!!!!!!!\n");
}

int main(int argc, char **argv, char **environ)
{
	int ret = 0;	

	signal(SIGINT, signal_fun);

/*
lable:	ret = pause();
	if(ret == -1 && errno == EINTR)
	{
		goto lable;
	}
*/
	
/*
	ret = 10;
lable1:	ret =sleep(ret);
	if(ret != 0)
	{
		printf("ret = %d\n", ret);
		goto lable1;
	}
*/

	char buf[100] = {0};
	read(0, buf, sizeof(buf));
	

	printf("hello\n");

	while(1);
	
	return 0;
}
