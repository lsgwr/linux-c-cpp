#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include  <arpa/inet.h>
#define MAX_LINE 100
int main(int argc, char *argv[])
{
	struct sockaddr_in sin;	/* 服务器的地址 */
	char buf[MAX_LINE];
	int s_fd;
	int port = 8000;
	char *str = "test sting";	/* 默认的字符串 */
	int n;
	if (argc > 1) {
		str = argv[1];			/* 从命令行参数中取得用户输入的串 */
	}
	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;	/* 使用IPv4地址族 */
	inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr); 
							   /*和本机通讯，同一台主机担任服务器和客户端的角色*/
	sin.sin_port = htons(port);/* 端口号使用8000，必须和服务器端的一致才行 */
	if( (s_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){ /* 创建套接字 */
		perror("fail to creat socket");
		exit(1);
	}
	if(connect(s_fd, (struct sockaddr *) &sin, sizeof(sin)) == -1){ 	/* 主动连接服务器 */
		perror("fail to connect");
		exit(1);
	}
	/* 使用send函数发送字符串，该串包含‘\0’结束符，不设置传输标志 */
	n = send(s_fd, str, strlen(str) + 1, 0);
	if(n == -1){ /* 写操作失败，程序退出 */
		perror("fail to send");
		exit(1);
	}
	/* 使用rec v函数接收字符串的大小，不设置传输标志 */
	n = recv(s_fd, buf, MAX_LINE, 0);
	if(n == -1){ /* 读失败，退出程序 */
		perror("fail to recv");
		exit(1);
	}
	printf("the length of str : %s\n", buf); /* 打印该串 */
	if(close(s_fd) == -1){ /* 关闭套接字，结束通信 */
		perror("fail to close");
		exit(1);
	}
	return 0;
}
