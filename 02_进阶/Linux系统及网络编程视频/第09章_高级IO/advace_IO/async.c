#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <poll.h>
#include <signal.h>



void print_err(char *str, int line, int err_no)
{
        printf("%d, %s: %s\n", line, str, strerror(err_no));
        exit(-1);
}


int mousefd = 0;
void signal_fun(int signo)
{
	int buf;
	int ret = 0;

	if(SIGIO == signo)
	{
		bzero(&buf, sizeof(buf));
		ret = read(mousefd, &buf, sizeof(buf));
		if(ret > 0) printf("%d\n", buf);
	}
}

int main(void)
{
	int ret = 0;
	char buf[100] = {0};
	struct pollfd fds[2];
	
	mousefd = open("/dev/input/mouse0", O_RDONLY);
	if(mousefd == -1) print_err("open mouse0 fail", __LINE__, errno);
		
	//为SIGIO设置捕获函数,在捕获函数里面读鼠标	
	signal(SIGIO, signal_fun);
	
	//告诉鼠标驱动,他发送的SIGIO信号由当前进程接收
	fcntl(mousefd, F_SETOWN, getpid());	

	//对mousefd进行设置,让其支持异步IO
	int flg = fcntl(mousefd, F_GETFL);
	flg |= O_ASYNC;
	fcntl(mousefd, F_SETFL, flg);
	
	
	while(1)
	{
		bzero(buf, sizeof(buf));
		ret = read(0, buf, sizeof(buf));
		if(ret > 0) printf("%s\n", buf);
	}

	return 0;
}


