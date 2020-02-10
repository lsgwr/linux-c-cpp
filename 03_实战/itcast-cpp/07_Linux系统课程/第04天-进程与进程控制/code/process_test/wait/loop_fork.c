#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int n = 5, i;				//默认创建5个子进程
    pid_t p, q;

	if(argc == 2){	
		n = atoi(argv[1]);
	}

	for(i = 0; i < n; i++)	 {//出口1,父进程专用出口
        p = fork();
		if(p == 0) {
			break;			//出口2,子进程出口,i不自增
        } else if (i == 3){
            q = p;
        }
    }

	if(n == i){
		sleep(n);
		printf("I am parent, pid = %d\n", getpid(), getgid());
        //pid_t pid = waitpid(q, NULL, WNOHANG);
//        pid_t pid = wait(NULL);
        //printf("child pid = %d\n", pid);
        while(1);

	} else {
		sleep(i);
		printf("I'm %dth child, pid = %d, gpid=%d\n", 
				i+1, getpid(), getgid());
        while(1);
	}

	return 0;
}
