#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void)
{
	pid_t pid;
	int num,status;
	pid = fork();								/* 创建第一个子进程 */
	if(pid < 0){
		perror("fail to fork");
		exit(1);
	}else if(pid == 0){
		printf("the first, exit normally\n");	/* 第一个子进程正常退出 */
		exit(0);
	}else{
		if(wait(&status) == -1){				/* 父进程等待子进程的退出 */
			perror("fail to wait");
			exit(1);
		}
		if(WIFEXITED(status) == 1) /* 得到正常退出的退出状态，exit函数的参数 */
			printf("the status of first is : %d\n", WEXITSTATUS(status));
	}
	pid = fork();				   /* 创建第二个子进程 */
	if(pid < 0){
		perror("fail to fork");
		exit(1);
	}else if(pid == 0){
		printf("the second, exit abnormally\n");
		num=1 / 0;					   /* 除以0，会产生SIGFPE异常信号 */
	}else{
		if(wait(&status) == -1){  /* 父进程等待子进程的退出 */
			perror("fail to wait");
			exit(1);
		}
		if(WIFSIGNALED (status) == 1) /* 得到终止子进程的信号的值 */
			printf("the terminated signal is : %d\n", WTERMSIG(status));
	}
	return 0;
}
