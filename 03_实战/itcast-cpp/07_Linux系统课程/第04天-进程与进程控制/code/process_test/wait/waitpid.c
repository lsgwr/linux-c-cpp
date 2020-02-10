#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid, pid2, wpid;
	int flg = 0;

	pid = fork();
	pid2 = fork();

	if(pid == -1){
		perror("fork error");
		exit(1);
	} else if(pid == 0){		//son
		printf("I'm process child, pid = %d\n", getpid());
		sleep(5);				
		exit(4);
	} else {					//parent
		do {
			wpid = waitpid(pid, NULL, WNOHANG);
            //wpid = wait(NULL);
			printf("---wpid = %d--------%d\n", wpid, flg++);
			if(wpid == 0){
				printf("NO child exited\n");
				sleep(1);		
			}
		} while (wpid == 0);		//子进程不可回收

		if(wpid == pid){		//回收了指定子进程
			printf("I'm parent, I catched child process,"
					"pid = %d\n", wpid);
		} else {
			printf("other...\n");
		}
	}

	return 0;
}
