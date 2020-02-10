#include <sys/wait.h>
#include <unistd.h>
int system(const char * cmdstring)
{
	pid_t pid;
	int status;
	if(cmdstring == NULL)	/* 如果命令字符串为空，则返回1 */
		return 1;
	pid = fork();			/* 创建一个子进程 */
	if(pid < 0){
		status = -1;
	}else if(pid == 0){		/* 子进程 */
		execl("/bin/sh", "sh", "-c", cmdstring, NULL); 
							/* 加载shell，由shell执行命令 */
		_exit(127);			/* 如果执行程序失败，子进程退出，返回127 */
	}
	if(waitpid(pid, &status, 0) == -1) /* wait函数出错，抛弃得到的无用状态 */
		status = -1;
	return status;						/* 返回退出状态 */
}
