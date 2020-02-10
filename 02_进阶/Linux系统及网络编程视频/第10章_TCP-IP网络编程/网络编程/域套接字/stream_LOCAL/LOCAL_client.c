#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <pthread.h>
#include <sys/un.h>


void print_err(char *str, int line, int err_no)
{
        printf("%d, %s: %s\n", line, str, strerror(err_no));
        exit(-1);
}

int sockfd = -1;

void *pth_fun(void *pth_arg)
{
	int ret = -1;
	char buf[100] = {0};
	while(1)
	{
		bzero(buf, sizeof(buf));
		ret = read(sockfd, buf,  sizeof(buf));
		if(ret == -1) print_err("socket fail", __LINE__, errno);
		else if(ret > 0) 
		{
			printf("%s\n", buf);
		}
	}
}

int main(void)
{
	int ret = 0;
	struct sockaddr_un seraddr = {0};	

	sockfd = socket(PF_UNIX, SOCK_STREAM, 0);
	if(sockfd == -1) print_err("socket fail", __LINE__, errno);

	seraddr.sun_family = AF_UNIX;
	strcpy(seraddr.sun_path, "./UNIX_SOCK");
	ret = connect(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));
	if(ret == -1) print_err("connect fail", __LINE__, errno);


	pthread_t tid;
	ret = pthread_create(&tid, NULL, pth_fun, NULL);	
	if(ret != 0) print_err("pthread_create fail", __LINE__, ret);	

	char buf[100] = {0};
	while(1)
	{
		bzero(buf, sizeof(buf));
		scanf("%s", buf);
		
		ret = write(sockfd, buf, sizeof(buf));	
		if(ret == -1) print_err("write fail", __LINE__, errno);
	}
	
	return 0;
}


