#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include "iolib.h" /* 用户自己的I/O函数库 */
#define MAX_LINE 80
int port = 8000; /*  */
/* 处理函数，用于将大写字符转换为小写字符。参数为需要转换的字符串 */
void my_fun(char * p)
{
	if(p == NULL) /* 空串 */
		return;
	for (; *p != '\0'; p++)
		if(*p >= 'A' && *p <= 'Z') /* 判断字符并进行转换，也可以使用库函数 */
			*p = *p -'A'+ 'a';
}
int main(void)
{
	struct sockaddr_in sin;
	struct sockaddr_in cin;
	int lfd;
	int cfd;
	int sfd;
	int rdy;
	int client[FD_SETSIZE];	/* 客户端连接的套接字描述符数组 */
	int maxi;
	int maxfd;					/* 最大连接数 */
	fd_set rset;
	fd_set allset;
	socklen_t addr_len;			/* 地址结构的长度 */
	char buf[MAX_LINE];
	char addr_p[INET_ADDRSTRLEN];
	int i;
	int n;
	int len;
	int opt = 1; /* 套接字选项 */
	bzero(&sin, sizeof(sin)); /* 填充地址结构 */
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port);
	/* 创建一个面向连接的套接字 */
	lfd = socket(AF_INET, SOCK_STREAM, 0);
	if (lfd == -1) {
		perror("call to socket");
		exit(1);
	}
	/* 设置套接字选项，使用默认选项 */
	setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	/* 绑定套接字到地址结构 */
	n = bind(lfd, (struct sockaddr *) &sin, sizeof(sin));
	if (n == -1) {
		perror("call to bind");
		exit(1);
	}
	/* 开始监听连接请求 */
	n = listen(lfd, 20);
	if (n == -1) {
		perror("call to listen"), exit(1);
	}
	printf("Accepting connections ...\n"); 
	maxfd = lfd;						/* 对最大文件描述符数进行初始化 */
	maxi = -1;
	for (i = 0; i < FD_SETSIZE; i++)	/* 初始化客户端连接描述符集合 */
		client[i] = -1;
	FD_ZERO(&allset);					/* 清空文件描述符集合 */
	FD_SET(lfd, &allset);				/* 将监听接字设置在集合内 */
	/* 开始服务器程序的死循环 */
	while(1){
		rset = allset;
		/* 得到当前可以读的文件描述符数 */
		rdy = select(maxfd + 1, &rset, NULL, NULL, NULL);
		if (FD_ISSET(lfd, &rset)){
			addr_len = sizeof(cin);
			/* 创建一个连接描述符 */
			cfd = accept(lfd, (struct sockaddr *) &cin, &addr_len);
			if(cfd == -1){
				perror("fail to accept");
				exit(1);
			}
			/* 查找一个空闲的位置 */
			for (i = 0; i < FD_SETSIZE; i++)
				if (client[i] < 0){
					client[i] = cfd; /* 将处理该客户端的连接套接字设置到该位置 */
					break;
				}
			
			/* 太多的客户端连接，服务器拒绝连接，跳出循环 */
			if (i == FD_SETSIZE){
				printf("too many clients");
				exit(1);
			}
			FD_SET(cfd, &allset);	/* 设置连接集合 */
			if (cfd > maxfd)		/* 新的连接描述符 */
				maxfd = cfd; 
			if (i > maxi)
				maxi = i;
			if (--rdy <= 0)			/* 减少一个连接描述符 */
				continue;
		}
		for (i = 0; i <= maxi; i++){ /* 对每一个连接描述符做处理 */
			if ((sfd = client[i]) < 0)
				continue;
			if (FD_ISSET(sfd, &rset)){
				n = my_read(sfd, buf, MAX_LINE); /* 读取数据 */
				if (n == 0){
					printf("the other side has been closed.\n");
					fflush(stdout);		/* 刷新到输出终端 */
					close(sfd);
					FD_CLR(sfd, &allset);	/* 清空连接描述符数组 */
					client[i] = -1;
				}else{
					/* 将客户端地址转换为字符串 */
					inet_ntop(AF_INET, &cin.sin_addr, addr_p, sizeof (addr_p));
					/* 打印客户端地址和端口号 */
					printf("client IP is %s, port is %d\n", addr_p, ntohs (cin.sin_port));
					printf("content is : %s\n", buf); /* 打印客户端发送过来的					字符串 */
					my_fun(buf); /* 调用大小写转换函数 */
					n = my_write(sfd, buf, len + 1);
					if(n == -1) /* 写函数出错 */
						exit(1);
				}
				if (--rdy <= 0)
					break;	/* 如果没有可以读的套接字则退出循环 */
			}
		}
	}
	close(lfd); /* 关闭链接套接字 */
	return 0;
}
