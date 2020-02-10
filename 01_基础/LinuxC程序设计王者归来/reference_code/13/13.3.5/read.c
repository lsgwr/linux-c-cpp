#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
/* SIGALRM信号的处理函数 */
void alrm_handler(int signo)
{
	/* 什么都不做，一个空的处理函数 */
}
/* 有限等待的read函数 */
size_t sig_read(int filefds, void *buf, size_t nbytes)
{
	size_t n;
	/* 加载SIGALRM的处理函数 */
	if(signal(SIGALRM, alrm_handler) == SIG_ERR){
		perror("fail to set handler for SIGALRM");
		exit(1);
	}
	alarm(5); /* 设置定时器，只等待5秒钟 */
	if((n = read(filefds, buf, nbytes)) == -1) /* 开始读操作，如果超时被中断，read函数返回-1 */
		return -1;
	alarm(0); /* 如果读成功，则取消定时器 */
	return n;
}
