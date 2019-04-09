#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <sys/un.h>


void print_err(char *str, int line, int err_no)
{
        printf("%d, %s: %s\n", line, str, strerror(err_no));
        exit(-1);
}

int cfd;

void *pth_fun(void *pth_arg)
{
	int ret = -1;
	char buf[100] = {0};
	while(1)
	{
		bzero(buf, sizeof(buf));
		ret = read(cfd, buf,  sizeof(buf));
		if(ret == -1) print_err("socket fail", __LINE__, errno);
		else if(ret > 0) 
		{
			printf("%s\n", buf);
		}
	}
}

void signal_fun(int signo)
{
	if(SIGINT == signo)
	{
		remove("./UNIX_SOCK");
		exit(-1);
	}
}

int main(void)
{
	int ret = 0;
	int sockfd = -1;
	struct sockaddr_un addr = {0};	


	signal(SIGINT, signal_fun);
	
	sockfd = socket(PF_UNIX, SOCK_STREAM, 0);
	if(sockfd == -1) print_err("socket fail", __LINE__, errno);

	/////////////////////////////////////////
	addr.sun_family = AF_UNIX;//AF_LOCAL
	strcpy(addr.sun_path, "./UNIX_SOCK");
	ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
	
	ret = listen(sockfd, 3);
	if(ret == -1) print_err("listen fail", __LINE__, errno);
	
	cfd = accept(sockfd, NULL, 0);
	if(cfd == -1) print_err("accept fail", __LINE__, errno);

	pthread_t tid;
	ret = pthread_create(&tid, NULL, pth_fun, NULL);	
	if(ret != 0) print_err("pthread_create fail", __LINE__, ret);	

	char buf[100] = {0};
	while(1)
	{
		bzero(buf, sizeof(buf));
		scanf("%s", buf);
		
		ret = write(cfd, buf, sizeof(buf));	
		if(ret == -1) print_err("write fail", __LINE__, errno);
	}
	
	return 0;
}


