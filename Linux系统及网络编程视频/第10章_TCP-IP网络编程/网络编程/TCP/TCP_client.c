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

/* 封装应用层数据, 目前要传输的是学生数据 */
//学生信息
typedef struct data
{
	unsigned int stu_num;
	char stu_name[50];
}Data;

void print_err(char *str, int line, int err_no)
{
        printf("%d, %s: %s\n", line, str, strerror(err_no));
        exit(-1);
}

int sockfd = -1;

void *pth_fun(void *pth_arg)
{
	int ret = 0;
	Data stu_data = {0};
	
	while(1)
	{
		bzero(&stu_data, sizeof(stu_data));
		
		ret = recv(sockfd, (void *)&stu_data, sizeof(stu_data), 0);
		if(ret > 0)
		{
			printf("student number:%d\n", ntohl(stu_data.stu_num));
			printf("student name:%s\n", stu_data.stu_name);
		}
		else if(ret == -1) print_err("recv fail", __LINE__, errno);
		
	}
}

void signal_fun(int signo)
{
	if(SIGINT == signo)
	{
		/* 断开连接 */
		//close(sockfd);
		shutdown(sockfd);

		exit(0);
	}
}

int main(void)
{
	int ret = 0;

	signal(SIGINT, signal_fun);

	/* 创建套接字文件,并指定使用TCP协议
	 * 对于客户端的套接字文件描述符来说,直接用于通信 */
	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if(sockfd == -1) print_err("socket fail", __LINE__, errno);
	
	/* 调用connect,想服务器主动请求连接 */
	struct sockaddr_in seraddr = {0};//用于存放你要请求连接的那个服务器的ip和端口
	
	seraddr.sin_family = AF_INET;//地址族
	seraddr.sin_port   = htons(SPORT);//服务器程序的端口
	seraddr.sin_addr.s_addr = inet_addr(SIP);//服务器的ip,如果是跨网通信的话,就是服务器的公网ip
	 
	ret = connect(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));
	if(ret == -1) print_err("connect fail", __LINE__, errno);

	pthread_t tid;
	ret = pthread_create(&tid, NULL, pth_fun, NULL);
	if(ret != 0) print_err("pthread_create fail", __LINE__, ret);


	Data stu_data  = {0};
	int tmp_num = 0;
	while(1)
	{
		bzero(&stu_data, sizeof(stu_data));
		/* 封入学生学号 */
		printf("input student number\n");	
		scanf("%d", &tmp_num);
		stu_data.stu_num = htonl(tmp_num);
		
		/* 封如学生名字 */
		printf("input student name\n");
		scanf("%s", stu_data.stu_name);
		
		ret = send(sockfd, (void *)&stu_data, sizeof(stu_data), 0);
		if(ret == -1) print_err("send fail", __LINE__, errno);
	}

	return 0;
}



