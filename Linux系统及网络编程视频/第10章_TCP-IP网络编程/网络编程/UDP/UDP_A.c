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

void print_err(char *str, int line, int err_no)
{
        printf("%d, %s: %s\n", line, str, strerror(err_no));
        exit(-1);
}

int sockfd = -1;


struct sockaddr_in peer_addr = {0};

void *pth_fun(void *pth_arg)
{
	int ret = -1;
	char buf[100] = {0};
	int peer_addr_size = 0;	

	while(1)
	{	
		bzero(buf, sizeof(buf));
		
		peer_addr_size = sizeof(peer_addr);	
		/* 接收对方发送的数据,并保存对方的ip和端口,以便回答 */
		ret = recvfrom(sockfd, buf, sizeof(buf), 0, \
			(struct sockaddr *)&peer_addr, &peer_addr_size);		
		if(ret == -1) print_err("recvfrom fial", __LINE__, errno);
		else if(ret > 0)
		{
			printf("peerip:%s, peerport:%d\n", \
			inet_ntoa(peer_addr.sin_addr), ntohs(peer_addr.sin_port));
			
			printf("%s\n", buf);
		}
	}
	
	return NULL;
}

int main(int argc, char **argv)
{
	int ret = 0;
	char buf[100] = {0};
	
	if(argc != 3)
	{
		printf("./a.out peer_ip peer_port\n");
		exit(-1);
	}

	/* 创建套接字文件,指定使用UDP协议 */
	sockfd = socket(PF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1) print_err("socket fial", __LINE__, errno);
	
	/* 使用UDP来通信,如果要接收数据的话,必须绑
	 * 定固定的IP和端口,方便对方发送数据 */
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port   = htons(5001);
	addr.sin_addr.s_addr = inet_addr("192.168.1.106"); 

	ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
	if(ret == -1) print_err("bind fial", __LINE__, errno);	
	
	/* 创建此线程,用于循环接收对方发送的数据 */
	pthread_t tid;
	ret = pthread_create(&tid, NULL, pth_fun, NULL);
	if(ret != 0) print_err("pthread_create fail", __LINE__, errno);
	
	/* 主线程发送数据 */	
	while(1)
	{
		/* 设置对方的IP和端口 */
		peer_addr.sin_family = AF_INET;
		peer_addr.sin_port  = htons(atoi(argv[2]));
		peer_addr.sin_addr.s_addr = inet_addr(argv[1]);

		bzero(buf, sizeof(buf));
		scanf("%s", buf);
		ret = sendto(sockfd, buf, sizeof(buf), 0, \
					(struct sockaddr *)&peer_addr, sizeof(peer_addr));
		if(ret == -1) print_err("sendto fial", __LINE__, errno);
	}

	return 0;
}





