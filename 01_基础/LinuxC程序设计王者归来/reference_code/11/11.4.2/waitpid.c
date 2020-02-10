#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void)
{
	pid_t pid;
	pid = fork();								/* 创建子进程 */
	if(pid < 0){
		printf("fail to fork\n");
		exit(1);
	}else if(pid == 0){							/* 创建子进程 */
		printf("the child\n");					/* 子进程休眠5秒钟 */
		sleep(5);
		exit(0);
	}else{
		printf("the parent\n");					/* 输出提示信息 */
		if(waitpid(pid, NULL, WNOHANG) == 0)	/* 非阻塞等待子进程 */
			printf("the child is not available now\n");
	}
	printf("no waiting, parent done\n");		/* 输出提示信息 */
	return 0;
}
