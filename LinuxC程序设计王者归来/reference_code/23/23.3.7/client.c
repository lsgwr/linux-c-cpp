#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include  <arpa/inet.h>
#include "iolib.h" /* I/O库函数的函数声明 */
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
	sin.sin_family = AF_INET; /* 使用IPv4地址族 */
	inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr); /* 和本机通讯，同一台主													 机担任服务器和客户端的角色 */
	sin.sin_port = htons(port); /* 端口号使用8000，必须和服务器端的一致才行 */
	if( (s_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){ /* 创建套接字 */
		perror("fail to creat socket");
		exit(1);
	}
	if(connect(s_fd, (struct sockaddr *) &sin, sizeof(sin)) == -1){		/* 主动连接服务器 */
		perror("fail to connect");
		exit(1);
	}
	n = my_write(s_fd, str, strlen(str) + 1); /* 发送字符串，该串包含‘\0’结																	束符 */
	if(n == -1) /* 写操作失败，程序退出 */
		exit(1);
	/* 读取服务器程序发回的串，由于是同一台主机通信，不存在延时的问题。
	* 但是在真正的网络环境中，要处理读操作的延时问题。
	*/
	n = my_read(s_fd, buf, MAX_LINE);
	if(n == -1) /* 读失败，退出程序 */
		exit(1);
	printf("recive from server: %s\n", buf); /* 打印该串 */
	if(close(s_fd) == -1){ /* 关闭套接字，结束通信 */
		perror("fail to close");
		exit(1);
	}
	return 0;
}
