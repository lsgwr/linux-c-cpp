#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(void)
{
	pid_t pid;
	pid = fork();		/* 创建一个子进程 */
	if(pid < 0){		/* 创建一个子进程失败 */
		perror("fail to fork");
		exit(1);
	}else if(pid == 0){
		/*===========调试用的辅助代码===========*/
		int check = 1;
		pid = getpid();		/* 得到进程的进程ID */
		while(check == 1)	/* 循环休眠等待调试 */
		sleep(1);
		/*===========辅助代码结束===========*/
		printf("the child done\n");
		exit(0);
	}else{
		if(wait(NULL) == -1){ /* 等待子进程执行结束 */
			perror("fail to wait");
			exit(1);
		}
		printf("the parent done\n"); /* 输出提示信息 */
	}
	return 0;
}
