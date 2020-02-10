#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
int main(void)
{
	struct sigaction act;
	pid_t pid;
	/* 设置sigaction结构
	* sa_handler : 采用默认的信号处理方式
	* sa_mask : 不屏蔽任何信号
	* sa_flags : 使用SA_NOCLDWAIT信号选项
	* sa_sigaction : 不使用备用信号处理函数
	*/
	act.sa_handler = SIG_DFL; 
	act.sa_flags = SA_NOCLDWAIT;
	act.sa_sigaction = NULL;
	sigemptyset(&act.sa_mask);
	/* 加载信号处理函数，实际目的只是为了设置信号选项 */
	if(sigaction(SIGCHLD, &act, NULL) == -1){
		perror("fail to set handler for SIGCHILD");
		exit(1);
	}
	pid = fork();						/* 创建第一个子进程 */
	if(pid < 0){
		perror("fail to fork");
		exit(1);
	}else if(pid == 0){
		printf("the 1st child\n");		/* 第一个子进程立即退出 */
		exit(0);
	}else{
		pid = fork();					/* 创建第二个子进程 */
		if(pid < 0){
			perror("fail to fork");
			exit(1);
		}else if(pid == 0){
			printf("the 2nd child\n");	/* 第二个子进程休眠5秒钟后退出 */
			sleep(5);
			exit(0);
		}else{
			if(wait(NULL) == -1)		/* 调用wait函数，该函数必定出错返回 */
				if(errno == ECHILD)
					printf("all child quit, no child is zome\n");
			
			printf("the parent\n");
		}
	}
	return 0;
}
