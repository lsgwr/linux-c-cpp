#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define MAX_LINE 100
/* 处理函数，用于将大写字符转换为小写字符。参数为需要转换的字符串 */
void my_fun(char * p)
{
	if(p == NULL)				 /* 空串 */
		return;
	for (; *p != '\0'; p++)
		if(*p >= 'A' && *p <= 'Z') /* 判断字符并进行转换，也可以使用库函数 */
			*p = *p -'A' + 'a';
}
int main(void)
{
	struct sockaddr_in sin;
	struct sockaddr_in cin;
	int l_fd;
	int c_fd;
	socklen_t len;
	char buf[MAX_LINE];					/* 存储传送内容的缓冲区 */
	char addr_p[INET_ADDRSTRLEN];		/* 存储客户端地址的缓冲区 */
	int port = 8000;					/* 端口号，使用8000 */
	int n;								/* 读写字节数 */
	bzero(&sin, sizeof(sin));			/* 清空地址结构 */
	sin.sin_family = AF_INET;			/* 使用IPv4通信域 */
	sin.sin_addr.s_addr = INADDR_ANY;	/* 服务器可以接受任意地址 */
	sin.sin_port = htons(port);		/* 端口号转换为网络字节序 */
	l_fd = socket(AF_INET, SOCK_STREAM, 0); /* 创立套接字，使用TCP协议 */
	bind(l_fd, (struct sockaddr*) &sin, sizeof(sin)); /* 将地址和套接字绑定 */
	listen(l_fd, 10);						/* 开始监听连接请求 */
	printf("waiting ...\n");
	while(1){/* 服务器程序多半是死循环 */
		/* 接受连接请求，从此函数中返回后就可以开始通信了 */
		c_fd = accept(l_fd, (struct sockaddr*) &cin, &len); 
		n = read(c_fd, buf, MAX_LINE);	/* 读取客户端传来的信息 */
		inet_ntop(AF_INET, &cin.sin_addr, addr_p, sizeof(addr_p));
											/* 将客户端地址转换为字符串 */
		printf("client IP is %s, port is %d\n", addr_p, ntohs(cin.sin_port)); 											/* 打印客户端地址和端口号 */
		printf("content is : %s\n", buf);	/* 打印客户端发送过来的字符串 */
		my_fun(buf);						/* 调用大小写转换函数 */
		write(c_fd, buf, n);				/* 将转换后的字串发给客户端 */
		close(c_fd);			/* 通信结束，关闭套接字，准备下一次通信 */
	}
	if(close(l_fd) == -1){		/* 通信结束，关闭套接字，准备下一次通信 */
		perror("fail to close");
		exit(1);
	}
	return 0; /* 不应该执行到这里 */
}
