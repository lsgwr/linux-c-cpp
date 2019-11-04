#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(void)
{
	pid_t pid;			/* 保存进程ID */
	pid = fork();		/* 创建一个新进程 */
	if(pid < 0){		/* fork出错 */
		printf("fail to fork\n");
		exit(1);
	}else if(pid == 0){	/* 子进程 */
		printf("this is child, pid is : %u\n", getpid()); 
						/* 打印子进程的进程ID */
	}else{
		printf("this is parent, pid is : %u, child-pid is : %u\n", getpid(), 
		pid);			/* 打印父进程和其子进程的进程ID */
	}
	return 0;
}
