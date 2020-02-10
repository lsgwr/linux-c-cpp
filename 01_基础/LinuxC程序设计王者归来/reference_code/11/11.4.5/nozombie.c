#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void)
{
	pid_t pid;
	pid = fork();				/* 创建子进程 */
	if(pid < 0){
		printf("fail to fork\n");
		exit(1);
	}else if(pid == 0){			/* 创建一个子进程 */
		printf("the child\n");
		pid = fork();			/* 创建一个子进程 */
		if(pid < 0){
			printf("fail to fork\n");
			exit(1);
		}else if(pid == 0){		/* 在此创建一个子进程（孙子进程），这个子进程处理实际工作 */
			printf("do something you want\n");
			sleep(5);			/* 子进程休眠 */
			printf("done\n");
			exit(0);
		}else{					/* 子进程退出，将孙子进程托付给init进程 */
			exit(0);
		}
	}else{
		if(waitpid(pid,NULL,0)>0)
			printf("child exited\n",pid);	/*等待子进程退出*/
		sleep(10);
		printf("the parent\n");	/* 输出提示信息 */
	}
	return 0;
}
