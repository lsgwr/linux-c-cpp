#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <strings.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define MAX_LINE 100
int main(int argc, char *argv[])
{
	struct sockaddr_in sin;	/* 服务器的地址 */
	char buf[MAX_LINE];
	int sfd;
	int port = 8000;
	char *str = "test sting";	/* 默认的字符串 */
	if (argc > 1) {
		str = argv[1];			/* 从命令行参数中取得用户输入的串 */
	}
	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;	/* 使用IPv4地址族 */
	/* 和本机通信，同一台主机担任服务器和客户端的角色 */
	inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr); 
	sin.sin_port = htons(port); /* 端口号使用8000，必须和服务器端的一致才行 */
	sfd = socket(AF_INET, SOCK_STREAM, 0);	/* 创建套接字 */
	connect(sfd, (const struct sockaddr *)&sin, sizeof(sin));
										/* 主动连接服务器 */
	write(sfd, str, strlen(str) + 1); /* 发送字符串，该串包含‘\0’结束符 */
	/* 读取服务器程序发回的串，由于是同一台主机通信，不存在延时的问题。
	* 但是在真正的网络环境中，要处理读操作的延时问题。
	*/
	read(sfd, buf, MAX_LINE); 
	printf("recive from server: %s\n", buf); /* 打印该串 */
	close(sfd);								   /* 关闭套接字，结束通信 */
	return 0;
}
