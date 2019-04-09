#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define RCVPORT 5009
#define BRD_ADDR "192.168.1.255"//广播地址

void err_fun(int line, char *funnam, int err_no)
{
    fprintf(stderr, "in %d, %s: %s\n", line, funnam, strerror(err_no));
    exit(-1);
}

int main(void)
{	
	char buf[300] = {0};
	int skfd = -1, ret = -1;
	struct sockaddr_in brdaddr = {0};

	skfd = socket(PF_INET, SOCK_DGRAM, 0);
	if(skfd < 0) err_fun(__LINE__, "socket", errno);
	
	int brdval = 1;
	/* 套接字选项设置
		参数1：套接字描述符
		参数2：设置级别，SOL_SOCKET，对所有协议都有效，如果只
			希望对某个协议设置，就是特殊级别，写协议号
		参数3：指定做什么样的功能设置
		参数4：使设置生效，一般来说，传一个非零，就可以生效
		参数5：第四个参数空间大小 */
	ret = setsockopt(skfd, SOL_SOCKET, SO_BROADCAST, &brdval, sizeof(4));
	if(ret < 0) err_fun(__LINE__, "setsockopt", errno);

	brdaddr.sin_family 	= AF_INET;
	brdaddr.sin_port 	= htons(RCVPORT);
	brdaddr.sin_addr.s_addr = inet_addr(BRD_ADDR);
	
	while(1)
	{	
		bzero(buf, sizeof(buf));
		ret = read(0, buf, sizeof(buf));	
		if(ret > 0) sendto(skfd, buf, strlen(buf), 0, \
			(struct sockaddr*)&brdaddr, sizeof(brdaddr));
	} 
	
	return 0;
}




