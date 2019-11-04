#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
/* 信号SIGUSR1的处理函数 */
void sigusr1_handler(int signo)
{
	printf("catch SIGUSR1\n");
	sleep(5); /* 等待下一个SIGUSR1信号 */
	printf("back to main\n");
}
int main(void)
{
	struct sigaction act;
	/* 设置sigaction结构
	* sa_handler : 使用sigusr1_handler处理函数
	* sa_mask : 不屏蔽任何信号
	* sa_flags : 使用SA_NODEFER信号选项
	*/
	act.sa_handler = sigusr1_handler; 
	act.sa_flags = SA_NODEFER;
	sigemptyset(&act.sa_mask);
	/* 加载信号处理函数，实际目的只是为了设置信号选项 */
	if(sigaction(SIGUSR1, &act, NULL) == -1){
		perror("fail to set handler for SIGUSR1");
		exit(1);
	}
	printf("process begin\n");
	sleep(15); /* 等待SIGUSR1信号 */
	printf("done\n");
	return 0;
}
