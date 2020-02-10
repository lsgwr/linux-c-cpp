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


/* 此线程接收客户端的数据 */
void *pth_fun(void *pth_arg)
{
	int ret = 0;
	Data stu_data = {0};
		
	while(1)
	{
		bzero(&stu_data, sizeof(stu_data));
		//ret = read(cfd, &stu_data, sizeof(stu_data));
		ret = recv(cfd, &stu_data, sizeof(stu_data), 0);
		if(ret == -1) print_err("recv fail", __LINE__, errno);
		else if(ret > 0)
		{	
			printf("student number = %d\n", ntohl(stu_data.stu_num));
			printf("student name = %s\n", stu_data.stu_name);
		}
	}
}

int main(void)
{
	int ret = -1;
	int sockfd = -1;
	

	signal(SIGINT, signal_fun);

	/* 创建使用TCP协议通信的套接字文件 */
	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if(sockfd == -1) print_err("socket fail", __LINE__, errno);

	/* 调用Bind绑定套接字文件/ip/端口 */
	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET;//制定ip地址格式(地址族)
	saddr.sin_port 	 = htons(SPORT);//服务器端口
	saddr.sin_addr.s_addr = inet_addr(SIP);//服务器ip
	
	ret = bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr));
	if(ret == -1) print_err("bind fail", __LINE__, errno);

	/* 讲主动的"套接字文件描述符"转为被动描述符,用于被动监听客户的连接 */
	ret = listen(sockfd, 3);
	if(ret == -1) print_err("listen fail", __LINE__, errno);
	
	/* 调用accept函数,被动监听客户的连接 */
	struct sockaddr_in clnaddr = {0};//存放客户的ip和端口
	int clnaddr_size = sizeof(clnaddr);

	cfd = accept(sockfd, (struct sockaddr *)&clnaddr, &clnaddr_size);
	if(cfd == -1) print_err("accept fail", __LINE__, errno);
	//打印客户的端口和ip, 一定要记得进行端序转换
	printf("clint_port = %d, clint_ip = %s\n", ntohs(clnaddr.sin_port), inet_ntoa(clnaddr.sin_addr));

	/* 创建一个次线程,用于接受客户发送的数据 */
	pthread_t tid;
	ret = pthread_create(&tid, NULL, pth_fun, NULL);
	if(ret != 0) print_err("pthread_create fail", __LINE__, ret);	

	Data stu_data = {0};
	int tmp_num;
	while(1)
	{
		bzero(&stu_data, sizeof(stu_data));
		/* 获取学生学号,但是需要讲让从主机端序转为网络端序 */
		printf("input student number\n");
		scanf("%d", &tmp_num);
		stu_data.stu_num = htonl(tmp_num);
		
		/* char的数据不需要进行端序的转换 */
		printf("input student name\n");
		scanf("%s", stu_data.stu_name);
	
		/* 发送数据 */	
		//ret = write(cfd, (void *)stu_data, sizeof(stu_data));
		ret = send(cfd, (void *)&stu_data, sizeof(stu_data), 0);
		if(ret == -1) print_err("send fail", __LINE__, errno);	
	}
	

	return 0;
}



