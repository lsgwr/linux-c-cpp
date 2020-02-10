#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(void)
{
	pid_t pid;
	pid = fork(); /* 创建子进程 */
	if(pid < 0){
		printf("fail to fork\n");
		exit(1);
	}else if(pid == 0){ /* 子进程 */
		/* 调用exec函数，运行当前目录下的hello程序，
		* 该程序不需要任何命令行参数，并且继承父进程的环境表 
		*/
		if(execvp("hello", NULL) < 0){
			printf("fail to exec\n");			/* exec失败则退出 */
			exit(0);
		}
		/* 这里应该永远不会执行，因为调用exec后这里的代码被hello程序所取代了 */
		printf("the child is not hello\n");	/* 绝对不会执行到这个位置 */
		exit(0);								/* 子进程正常退出 */
		}
		printf("the parent\n");					/* 父进程 */
		return 0;
}
