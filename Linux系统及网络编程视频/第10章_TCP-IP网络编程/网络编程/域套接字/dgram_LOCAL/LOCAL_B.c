#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <sys/un.h>


void print_err(char *str, int line, int err_no)
{
        printf("%d, %s: %s\n", line, str, strerror(err_no));
        exit(-1);
}

int sockfd = -1;
struct sockaddr_un peer_addr;

void *pth_fun(void *pth_arg)
{
	int ret = -1;
	char buf[100] = {0};
	int peer_addr_size = sizeof(peer_addr);

	while(1)
	{
		bzero(buf, sizeof(buf));
		
		ret = recvfrom(sockfd, buf, sizeof(buf), 0, \
				(struct sockaddr *)&peer_addr, &peer_addr_size);		
		if(ret == -1) print_err("recvfrom fail", __LINE__, errno);
		else if(ret > 0) 
		{
			printf("%s\n", buf);
		}
	}
}

void signal_fun(int signo)
{
	if(SIGINT == signo)
	{
		remove("./unix_sock_B");
		exit(-1);
	}
}

int main(int argc, char **argv)
{
	int ret = -1;


	if(argc != 2)
	{
		printf("./a.out peer_file\n");
		exit(-1);
	}

	signal(SIGINT, signal_fun);

	sockfd = socket(PF_UNIX, SOCK_DGRAM, 0);
	if(sockfd == -1) print_err("socket fail", __LINE__, errno);
	
	struct sockaddr_un addr;
	addr.sun_family = AF_UNIX;
	strcpy(addr.sun_path, "./unix_sock_B");
	ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));	

	pthread_t tid;
	ret = pthread_create(&tid, NULL, pth_fun, NULL);
	if(ret != 0) print_err("pthread_create fail", __LINE__, ret);
	
	char buf[100] = {0};
	while(1)
	{
		peer_addr.sun_family = AF_UNIX;
		strcpy(peer_addr.sun_path, argv[1]);

		bzero(buf, sizeof(buf));
		scanf("%s", buf);
		
		ret = sendto(sockfd, buf, sizeof(buf), 0, \
				(struct sockaddr *)&peer_addr, sizeof(peer_addr));		
		if(ret == -1) print_err("sendto fail", __LINE__, errno);
	}

	return 0;
}


