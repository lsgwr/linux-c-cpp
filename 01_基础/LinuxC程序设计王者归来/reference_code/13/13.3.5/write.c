#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
/* SIGALRM信号的处理函数 */
void alrm_handler(int signo)
{
	/* 什么都不做，一个空的处理函数 */
}
/* 有限等待的write函数，参数和返回值和read函数一样 */
size_t sig_read(int filefds, void *buf, size_t nbytes)
{
	size_t n;
	/* 加载SIGALRM的处理函数 */
	if(signal(SIGALRM, alrm_handler) == SIG_ERR){
		perror("fail to set handler for SIGALRM");
		exit(1);
	}
	alarm(5); /* 设置定时器，只等待5秒钟 */
	if((n = write(filefds, buf, nbytes)) == -1) /* 开始写操作，如果超时被中断，write函数返回-1 */
		return -1;
	alarm(0); /* 如果写成功，则取消定时器 */
	return n;
}
