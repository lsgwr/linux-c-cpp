#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#define MAX_LINE 80
int main(void)
{
	struct sockaddr_in sin;
	struct sockaddr_in cin;
	int port = 8000;
	socklen_t addr_len;
	int s_fd;
	char *buf;
	int n,flags;
	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;						  /* 使用IP地址族 */
	inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr);  /* 与本机的服务器程序通信，使用本机的IP地址 */
	sin.sin_port = htons(port);						  /* 转换端口号 */
	/* 创建一个无连接套接字 */
	s_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(s_fd == -1){
		perror("fail to create socket");
		exit(1);
	}
	
	printf("sendto=");
	/* 从标准输入读入一个字符串，如果用户不输入‘\n’结束符，会一直阻塞，导致套接字数据未准备好 */
	//if(fgets(buf, MAX_LINE, stdin) == NULL){
	//	perror("fail to get a line");
	//	exit(1);
	//}
	buf="hello\0";
	/* 使用服务器的地址结构，向服务器发送该字符串 */
	n = sendto(s_fd, buf, strlen(buf) + 1, 0, (struct sockaddr *) &sin,sizeof(sin));
	printf("sendto=%d",n);
	if(n == -1){
		perror("fail to send\n");
		exit(1);
	}
	/* 接受服务器端发送过来的转换后的字符串，并且得到服务器端的地址 */
	n = recvfrom(s_fd, buf, MAX_LINE, 0, (struct sockaddr *) &cin, &addr_len);
	printf("recv=%d",n);
	if(n == -1){
		perror("fail to receive\n");
		exit(1);
	}else
		printf("recive from server: %s\n", buf); /* 打印该串 */
	if(close(s_fd) == -1){ /* 关闭套接字 */
		perror("fail to close.\n");
		exit(1);
	}
	return 0;
}
