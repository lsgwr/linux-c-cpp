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



void print_err(char *str, int line, int err_no)
{
        printf("%d, %s: %s\n", line, str, strerror(err_no));
        exit(-1);
}


int main(void)
{
	int ret = 0;
	int mousefd = 0;
	char buf1[100] = {0};
	int buf2 = 0;
	struct pollfd fds[2];
	
	mousefd = open("/dev/input/mouse0", O_RDONLY);
	if(mousefd == -1) print_err("open mouse0 fail", __LINE__, errno);
		
	fds[0].fd = 0;
	fds[0].events = POLLIN;

	fds[1].fd = mousefd;
	fds[1].events = POLLIN; //期望的事件

	while(1)
	{
	lable:	ret = poll(fds, 2, 3000);	
		if(ret==-1 && errno==EINTR) goto lable; //重启系统调用
		else if(ret == -1) print_err("poll fail", __LINE__, errno);
		if(ret > 0) 
		{
			if(fds[0].events == fds[0].revents)
			{
				bzero(buf1, sizeof(buf1));
				ret = read(fds[0].fd, buf1, sizeof(buf1));
				if(ret > 0) printf("%s\n", buf1);
			}
			if(fds[1].events == fds[1].revents)
			{
				bzero(&buf2, sizeof(buf2));
				ret = read(fds[1].fd, &buf2, sizeof(buf2));
				if(ret > 0) printf("%d\n", buf2);
			}
		}	
		else if(ret == 0) printf("tome out\n");		
	}	
	
	return 0;
}


