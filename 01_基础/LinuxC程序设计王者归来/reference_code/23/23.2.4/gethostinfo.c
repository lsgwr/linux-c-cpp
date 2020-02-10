#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>
#define NET_ADDR 16			/* 16个字节，用于存放点分十进制IP地址的字符串 */
int main(void)
{
	struct hostent * host;	/* 用于存放主机信息 */
	char addr_p[NET_ADDR];	/* 用于存储点分十进制IP地址的字符串 */
	int i;
	if((host = gethostent()) == NULL){ /* 获得主机信息 */
		perror("fail to get host’s information\n");
		exit(1);
	}
	printf("%s\n", host->h_name);					/* 打印主机名 */
	for(i = 0; host->h_aliases[i] != NULL; i++)	/* 打印主机别名 */
		printf("%s\n", host->h_aliases[i]);
	if(host->h_addrtype == AF_INET)				/* 打印地址类型	*/
		printf("af_inet\n");
	else
		printf("unix_inet\n");
	printf("%d\n", host->h_length);				/* 打印地址长度 */
	for(i = 0; host->h_addr_list[i] != NULL; i++)	/* 打印主机IP地址 */
		/* 该地址以二进制数形式存储，转换为字符串形式 */
		printf("%s\n", inet_ntop(host->h_addrtype,host->h_addr_list[i], addr_p, NET_ADDR));
	return 0;
}
