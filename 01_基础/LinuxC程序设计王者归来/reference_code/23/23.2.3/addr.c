#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
/* 该程序只演示IPv4的地址转换 */
int main(void)
{
	char addr_p[16];		/* IP地址的点分十进制字符串表示形式*/
	struct in_addr addr_n;	/* IP地址的二进制表示形式 */
	if(inet_pton(AF_INET, "192.168.11.6", &addr_n) == -1){ /* 地址由字符串转															换为二进制数 */
		perror("fail to convert");
		exit(1);
	}
	
	printf("address : %x\n", addr_n.s_addr);  /* 打印地址的十六进制形式，这样更便于阅读 */
	/* 地址由二进制数转换为点分十进制字符串 */
	if(inet_ntop(AF_INET, &addr_n, &addr_p, sizeof(addr_p)) == -1){
		perror("fail to convert");
		exit(1);
	}
	printf("address : %s\n", addr_p);  /* 打印地址的点分十进制形式 */
	return 0;
}
