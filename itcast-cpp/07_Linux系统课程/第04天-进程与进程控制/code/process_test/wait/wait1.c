#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid, wpid;

	pid = fork();

	if(pid == -1){
		perror("fork error");
		exit(1);
	} else if(pid == 0){		//son
		printf("I'm process child, pid = %d\n", getpid());
		sleep(7);				//困了...
	} else {
lable:
		wpid = wait(NULL);		//死等!!!
		if(wpid == -1){
			perror("wait error");
			goto lable;
		}
		printf("I'm parent, I catched child process,"
				"pid = %d\n", wpid);
	}

	return 0;
}
