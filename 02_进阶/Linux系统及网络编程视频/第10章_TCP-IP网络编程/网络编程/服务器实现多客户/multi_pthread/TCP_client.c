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
	long sockfd = (long)ptharg;
	char buf[100] = {0};
	
	while(1)
	{
		bzero(buf, sizeof(buf));
		ret = recv(sockfd, buf, sizeof(buf), 0);
		if(ret == -1) print_err("recv fail", __LINE__, errno);
		else if(ret > 0)
		{
			printf("server answer: %s\n", buf);
		}
	}

	return NULL;
}

int main(void)
{
	int ret = -1;
	long sockfd = -1;	
	struct sockaddr_in seraddr;	
	
	
	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if(sockfd == -1) print_err("socket fail", __LINE__, errno);
	
	seraddr.sin_family = AF_INET;
	seraddr.sin_port   = htons(5007);
	seraddr.sin_addr.s_addr = inet_addr("192.168.1.106");
	ret = connect(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));
	if(ret == -1) print_err("connect fail", __LINE__, errno);
		
	pthread_t tid;
	ret = pthread_create(&tid, NULL, pth_fun, (void *)sockfd);
	if(ret != 0) print_err("pthread_create fail", __LINE__, ret);

	char buf[100] = {0};
	while(1)
	{	
		bzero(buf, sizeof(buf));
		scanf("%s", buf);
		ret = send(sockfd, buf, sizeof(buf), 0);
		if(ret == -1) print_err("send fail", __LINE__, errno);
	}
	
	
	return 0;
}



