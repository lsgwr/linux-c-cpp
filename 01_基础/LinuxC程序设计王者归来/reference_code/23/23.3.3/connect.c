#include <unistd.h>
#include <sys/socket.h>
#define SLEEP_SEC 60  /* 休眠时间，1分钟 */
#define MAX_TIMES 10  /* 最大连接次数 */
/* 该函数的参数和connect函数一样，其作用只是检查connect函数返回的错误 */
int connect_poll(int sockfd, const struct sockaddr * addr, socklen_t len)
{
	int count;
	for(count = 0; count <= MAX_TIMES; count ++){ /* 连接次数过多，则放弃连接 */
		if(connect(sockfd, addr, len) == 0)
			return 0;
		sleep(SLEEP_SEC); /* 延时，等待下一次尝试连接 */
	}
	return -1;
}
