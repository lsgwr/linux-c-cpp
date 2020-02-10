#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
/* 信号SIGUSR1的处理函数 */
void sigusr1_handler(int signo)
{
	printf("catch SIGUSR1\n");
}
int main(void)
{
	struct sigaction act;
	/* 设置sigaction结构
	* sa_handler : 使用sigusr1_handler处理函数
	* sa_mask : 不屏蔽任何信号
	* sa_flags : 使用SA_RESETHAND信号选项
	*/
	act.sa_handler = sigusr1_handler; 
	act.sa_flags = SA_RESETHAND;
	sigemptyset(&act.sa_mask);
	/* 加载信号处理函数，实际目的只是为了设置信号选项 */
	if(sigaction(SIGUSR1, &act, NULL) == -1){
		perror("fail to set handler for SIGCHILD");
		exit(1);
	}
	printf("process begin\n");	/* 输出提示信息 */
	sleep(15);					/* 等待第一个siGUSR1信号 */
	sleep(15);					/* 等待第二个siGUSR1信号 */
	printf("done\n");			/* 输出提示信息，进程结束 */
	return 0;
}
