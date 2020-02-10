#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define MAX_LINE 100
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
	if( (l_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){ /* 创立套接字，使															   用TCP协议 */
		perror("fail to creat socket");
		exit(1);
	}
	if(bind(l_fd, (struct sockaddr *) &sin, sizeof(sin)) == -1){ /* 将地址																 和套接字绑定 */
		perror("fail to bind");
		exit(1);
	}
	if(listen(l_fd, 10) == -1){ /* 开始监听连接请求 */
		perror("fail to listen");
		exit(1);
	}
	printf("waiting ...\n");
	while(1){/* 服务器程序多半是死循环 */
		if( (c_fd = accept(l_fd, (struct sockaddr *) &cin, &len)) == -1){
		/* 接受连接请求，从此函数中返回后就可以开始通信了 */
			perror("fail to accept");
			exit(1);
		}
		/* 调用recv函数读取客户端传来的信息，不设置任何特殊的标志 */
		n = recv(c_fd, buf, MAX_LINE, 0);
		if(n == -1){ /* 读取出错，my_read函数做错误处理，读入字节为-1则退出 */
			perror("fail to receive");
			exit(1);
		}else if(n == 0){ /* 通信的另一个端已经关闭 */
			printf("the connect has been closed\n");
			close(c_fd); /* 关闭通信用的套接字，注意监听套接字没有关闭 */
			continue;	  /* 此次连接处理结束，准备处理下一个连接 */
		}
		inet_ntop(AF_INET, &cin.sin_addr, addr_p, sizeof(addr_p));
						/* 将客户端地址转换为字符串 */
		printf("client IP is %s, port is %d\n", addr_p, ntohs(cin.sin_port)); 						/* 打印客户端地址和端口号 */
		printf("content is : %s\n", buf);	/* 打印客户端发送过来的字符串 */
		n = strlen(buf);					/* 得到客户端传输的字符串的长度 */
		sprintf(buf, "%d", n);				/* 将该长度传回 */
		/* 使用send函数将转换后的字串发给客户端，不设置任何特殊的标志 */
		n = send(c_fd, buf, strlen(buf) + 1, 0);
		if(n == -1){ /* 写失败则退出 */
			perror("fail to send");
			exit(1);
		}
		if(close(c_fd) == -1){ /* 通讯结束，关闭套接字，准备下一次通信 */
			perror("fail to close");
			exit(1);
		}
	}
	return 0; /* 不应该执行到这里 */
}
