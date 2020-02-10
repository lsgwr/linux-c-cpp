#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>



int main(void)
{
	pid_t ret = 0;
	

	printf("befor fork\n");

	ret = fork();
	if(ret > 0)
	{
		printf("parent PID = %d\n", getpid());
		printf("parent ret = %d\n", ret);
		sleep(1);
	}
	else if(ret == 0)
	{
		printf("child PID = %d\n", getpid());
		printf("child ret = %d\n", ret);
	}
	

	printf("after fork\n\n");

//	while(1);
	
	
	return 0;
}
