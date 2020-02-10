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
	fd_set readfds;
	struct timeval timeover;
	
	mousefd = open("/dev/input/mouse0", O_RDONLY);
	if(mousefd == -1) print_err("open mouse0 fail", __LINE__, errno);
	
		
	while(1)
	{
		/* 经0和mousefd加入读集合 */
		FD_ZERO(&readfds);
		FD_SET(0, &readfds);
		FD_SET(mousefd, &readfds);
		
		/* 设置超时时间 */
		timeover.tv_sec = 3;	
		timeover.tv_usec = 0;

		/* select监听:如果集合没有动静就阻塞 */
	lable:	ret = select(mousefd+1 , &readfds, NULL, NULL, &timeover);
		if(ret==-1 && errno==EINTR) goto lable;
		else if(ret == -1) print_err("select fail", __LINE__, errno);
		else if(ret > 0) 
		{
			if(FD_ISSET(0, &readfds))
			{
				bzero(buf1, sizeof(buf1));
				ret = read(0, buf1, sizeof(buf1));	
				if(ret > 0) printf("%s\n", buf1);
			}		
			if(FD_ISSET(mousefd, &readfds))
			{
				bzero(&buf2, sizeof(buf2));
				ret = read(mousefd, &buf2, sizeof(buf2));	
				if(ret > 0) printf("%d\n", buf2);
			}
		}
		else if(ret == 0)
		{
			printf("time out\n");
		}
	}	
	
	return 0;
}


