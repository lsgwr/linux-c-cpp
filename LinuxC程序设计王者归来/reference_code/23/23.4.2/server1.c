#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#define MAX_LINE 100
/* 处理函数，用于将大写字符转换为小写字符。参数为需要转换的字符串 */
void my_fun(char * p)
{
	if(p == NULL)					/* 空串 */
		return;
	for (; *p != '\0'; p++)
		if(*p >= 'A' && *p <= 'Z')	/* 判断字符并进行转换，也可以使用库函数 */
			*p = *p - 'A' + 'a';
}
int main(void)
{
	struct sockaddr_in sin;
	struct sockaddr_in cin;
	int s_fd;
	int port = 8000;				/* 端口号 */
	socklen_t addr_len;
	char buf[MAX_LINE];
	char addr_p[INET_ADDRSTRLEN];	/* 存放IP地址的缓冲区 */
	int n, flags;
	/* 填写地址结构 */
	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port);
	/* 使用UDP通信协议创建一个套接字，并且得到发送本数据包的客户端的地址 */
	s_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (s_fd == -1) {
		perror("fail to create socket");
		exit(1);
	}
	if(bind(s_fd, (struct sockaddr *) &sin, sizeof(sin)) == -1){ 										/* 将套接字绑定到一个地址 */
		perror("call to bind");
		exit(1);
	}
	flags = fcntl(s_fd, F_GETFL);
	flags |= O_NONBLOCK; /* 设置套接字为非阻塞套接字的标志 */
	/* 设置套接字为非阻塞套接字，修改之后服务器程序在套接字不可用时不会休眠等待 */
	if(fcntl(s_fd, F_SETFL, flags) == -1){
		perror("fail to fcntl");
		exit(1);
	}
	/* 服务器是一个死循环，一次循环处理一个请求 */
	while (1) {
		sleep(5); /* 休眠5秒钟，等待数据可用 */
		addr_len = sizeof(cin);
		/* UDP协议是无连接的，所以只有一个套接字接受客户端传输的数据包即可
		* 而不需要再创建一个额外的套接字用于建立连接
		* 同样的使用UDP协议的网络程序也不需要调用accept函数
		*/
		/* 接受客户端传送过来的字符串 */
		n = recvfrom(s_fd, buf, MAX_LINE, 0, (struct sockaddr *) &cin,&addr_len);
		if ((n == -1) && (errno != EAGAIN)) { /* 如果读写操作因为套接字未准备好而返回-1，则不算作出错 */
			perror("fail to receive\n");
			exit(1);
		}else if(errno == EAGAIN){
			printf("socket are not ready now\n");
			continue;
		}
		inet_ntop(AF_INET, &cin.sin_addr, addr_p, addr_len); 					/* 将客户端地址转换为字符串 */
		printf("client IP is %s, port is %d\n", addr_p, ntohs(cin.sin_port)); 		/* 打印客户端地址和端口号 */
		printf("content is : %s\n", buf); /* 打印客户端发送过来的字符串 */
		my_fun(buf); /* 调用大小写转换函数 */
		//printf("buf=%s",buf);
		/* 使用sendto函数将转换后的字符串传回给客户端程序 */
		n = sendto(s_fd, buf, n, 0, (struct sockaddr *) &cin, addr_len);
		if (n == -1 && errno != EAGAIN){ /* 如果读写操作因为套接字未准备好而返回-1，则不算作出错 */
			perror("fail to send\n");
			exit(1);
		}
		else if(errno == EAGAIN){
			printf("socket are not ready now\n");
			continue;
		}
	}
	if(close(s_fd) == -1){ /* 只需要关闭一个唯一的套接字即可 */
		perror("fail to close");
		exit(1);
	}
	return 0;
}
