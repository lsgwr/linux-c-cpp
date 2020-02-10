#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include "iolib.h" /* 添加用户自己的I/O函数库 */
#define MAX_LINE 80
int main(int argc, char *argv[])
{
   	struct sockaddr_in sin;
   	int port = 8000; /* 端口号，使用8000端口 */
	int s_fd;
	char buf[MAX_LINE];
   	char *str = "test";
   	char addr_p[INET_ADDRSTRLEN];
   	int n;
	if(argc == 2)
		str = argv[1];
	memset(&sin, sizeof(sin), 0);			/* 设置地址结构 */
    sin.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr);
    sin.sin_port = htons(port);
   	s_fd = socket(AF_INET, SOCK_DGRAM, 0); /* 建立一个使用UDP协议的套接字 */
    if(s_fd == -1){
		perror("fail to create socket");
        exit(1);
     }
	/* 使用connect函数与服务器进行连接，连接之后就相当于使用一个TCP的套接字进行通信了 */
     n = connect(s_fd, (struct sockaddr *) &sin, sizeof(sin));
     if(n == -1){
          perror("fail to connect");
          exit(1);
     }else
		printf("connection has been established\n");
    n = my_write(s_fd, str, strlen(str)+1); /* 发送字符串，该串包含‘\0’结束符 */
	if(n == -1) /* 写操作失败，程序退出 */
		exit(1);
	/* 读取服务器程序发回的串，由于是同一台主机通信，不存在延时的问题
	* 但是在真正的网络环境中，要处理读操作的延时问题
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
