#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>



void print_err(char *str, int line, int err_no)
{
        printf("%d, %s: %s\n", line, str, strerror(err_no));
        exit(-1);
}


int main(int argc, char **argv)
{	
	int ret = 0;
	int cfd = atoi(argv[1]);
	char buf[100] = {0};	

	printf("in new_pro, cfd = %d\n", cfd);

	while(1)
	{
		ret = recv(cfd, buf, sizeof(buf), 0);	
		if(ret == -1) print_err("recv fail", __LINE__, errno);
		else if(ret > 0)
		{
			printf("client say: %s\n", buf);
			ret = send(cfd, "recv ok!", sizeof("recv ok!"), 0);
			if(ret == -1) print_err("send fail", __LINE__, errno);
		}
	}
	
	return 0;
}	



