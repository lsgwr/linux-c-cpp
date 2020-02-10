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


#define MYPORT 5009
#define MYADDR "192.168.1.34"

void err_fun(int line, char *funnam, int err_no)
{
    fprintf(stderr, "in %d, %s: %s\n", line, funnam, strerror(err_no));
    exit(-1);
}

int main(void)
{	
	socklen_t clen = -1;
	char buf[300] = {0};
	int skfd = -1, ret = -1;
	struct sockaddr_in myaddr = {0};
	struct sockaddr_in sndaddr = {0};

	skfd = socket(PF_INET, SOCK_DGRAM, 0);
	if(skfd < 0) err_fun(__LINE__, "socket", errno);
	
	bzero(&myaddr, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(MYPORT);
	myaddr.sin_addr.s_addr = htons(INADDR_ANY);
	//myaddr.sin_addr.s_addr = inet_addr(MYADDR);
	ret = bind(skfd, (struct sockaddr*)&myaddr, sizeof(myaddr));
	if(ret < 0) err_fun(__LINE__, "bind", errno);
	
	clen = sizeof(sndaddr);
	while(1)
	{
		memset(buf, 0, sizeof(buf));
		ret = recvfrom(skfd, buf, sizeof(buf), 0, \
				(struct sockaddr*)&sndaddr, &clen);
		if(ret > 0)
		{
			printf("sndport %d, sndip %s: ", ntohs(sndaddr.sin_port), \
				inet_ntoa(sndaddr.sin_addr));
			printf("%s\n", buf);
		}
	}
	
	return 0;
}




