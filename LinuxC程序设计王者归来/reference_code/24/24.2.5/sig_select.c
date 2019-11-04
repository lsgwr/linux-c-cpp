#include <stdio.h>
#include <sys/select.h>
#include <stdlib.h>
#include <signal.h>
/* SIGUSR1的信号处理函数 */
void sigusr1_handler(int signo)
{
	printf("catch SIGUSR1\n"); /* 接收SIGUSR1信号，打印接收信息 */
}
int main()
{
	int rdy; /* 准备好的设备数 */
	/* 注册信号处理函数，如果捕捉到信号则输出提示信息 */
	if(signal(SIGUSR1, sigusr1_handler) == SIG_ERR){
		perror("can’t set handler for SIGUSR1");
		exit(1);
	}
	/* 不关心所有的设备准备状态，所以检查设备的最大文件描述符的值也不再有意义。
	* 等待时间结构为NULL，表示将等待时间设置为无限等待
	*/
	rdy = select(1, NULL, NULL, NULL, NULL);
	/* 因为是无限等待，所以绝对不应该执行到这里，输出提示信息 */
	printf("should never be here\n");
	return 0;
}
