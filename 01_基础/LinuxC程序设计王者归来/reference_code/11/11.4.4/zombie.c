#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(void)
{
	pid_t pid;
	pid = fork();					/* 创建子进程 */
	if(pid < 0){					/* 创建子进程出错 */
		printf("fail to fork\n");
		exit(0);
	}else if(pid == 0){				/* 创建子进程 */
		printf("the child\n");
		sleep(5);					/* 子进程休眠5秒钟 */
		printf("done\n");			/* 输出提示信息 */
		exit(0);
	}else
		printf("the parent\n");		/* 输出提示信息 */
		sleep(30);					/* 在这30秒的时间内子进程是一个僵尸进程 */
		if(wait(NULL) == -1){		/* 等待子进程结束 */
		perror("fail to wait");
		exit(1);
	}
	return 0;
}
