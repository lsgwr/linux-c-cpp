#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
	pid_t pid;
	pid = fork();	 /* 创建一个子进程 */
	if(pid < 0){
		printf("fail to fork\n");
		exit(1);
	}else if(pid == 0){ /* 子进程 */
		/* 使用execl函数执行程序，命令行参数列表使用NULL结尾。
		* 该程序使用三个参数，第一个是解释器文件的文件名 
		*/
		execl("/home/linux-c/interp.sh", "interp", "arg1", "arg2", NULL); 
		_exit(0);	 /* 调用_exit函数退出 */
	}
	exit(0);		 /* 父进程直接退出 */
}
