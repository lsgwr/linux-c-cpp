#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>


#define SPORT 5006
#define SIP "192.168.1.106"


void print_err(char *str, int line, int err_no)
{
        printf("%d, %s: %s\n", line, str, strerror(err_no));
        exit(-1);
}

int cfd = -1;//存放与连接客户通信的通信描述符

void signal_fun(int signo)
{
	if(signo == SIGINT)
	{	
		//断开连接
		//close(cfd);
		shutdown(cfd, SHUT_RDWR);
		
		exit(0);
	}
}

void *pth_fun(void *ptharg)
{
	int ret = -1;
	long cfd = (long)ptharg;
	char buf[100] = {0};
	
	while(1)
	{
		bzero(buf, sizeof(buf));
		ret = recv(cfd, buf, sizeof(buf), 0);
		if(ret == -1) print_err("recv fail", __LINE__, errno);
		else if(ret > 0)
		{
			printf("client say: %s\n", buf);
			ret = send(cfd, "recv ok\n", sizeof("recv ok\n"), 0);
			if(ret == -1) print_err("send fail", __LINE__, errno);
		}
	}

	return NULL;
}

int main(void)
{
	int ret = -1;
	int sockfd = -1;	
	struct sockaddr_in addr;	
	
	
	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if(sockfd == -1) print_err("socket fail", __LINE__, errno);
	
	addr.sin_family = AF_INET;
	addr.sin_port   = htons(5007);
	addr.sin_addr.s_addr = inet_addr("192.168.1.106");
	ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
	if(ret == -1) print_err("bind fail", __LINE__, errno);
	
	ret = listen(sockfd, 3);
	if(ret == -1) print_err("listen fail", __LINE__, errno);
	
	long cfd; 
	pthread_t tid;
	while(1)
	{
		cfd = accept(sockfd, NULL, NULL);
		if(cfd == -1) print_err("accept fail", __LINE__, errno);

		ret = pthread_create(&tid, NULL, pth_fun, (void *)cfd);
		if(ret != 0) print_err("pthread_create fail", __LINE__, ret);
	}
	
	
	return 0;
}



