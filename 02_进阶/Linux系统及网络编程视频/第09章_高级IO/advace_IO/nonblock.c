#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


void print_err(char *str, int line, int err_no)
{
        printf("%d, %s: %s\n", line, str, strerror(err_no));
        exit(-1);
}


int main(void)
{	
	int cor; //存放鼠标光标的坐标
	int mousefd = -1;
	int ret = 0;
	char buf[100] = {0};

	//mousefd = open("/dev/input/mouse0", O_RDONLY|O_NONBLOCK);
	//if(mousefd == -1) print_err("open mouse0 fail", __LINE__, errno);

	
	//重设0
	//fcntl(0, F_SETFL, O_RDONLY|O_NONBLOCK);
	
	//补设
	int flag = fcntl(0, F_GETFL);
	flag = flag | O_NONBLOCK;
	fcntl(0, F_SETFL, flag); 
	

	while(1)
	{
		//printf("111\n");
		//ret = read(mousefd, &cor, sizeof(cor));	
		//if(ret > 0) printf("%u\n", cor);
		//else if(ret==-1 && errno!=EAGAIN) print_err("read mouse0 fail", __LINE__, errno);
			
		//ret = read(0, buf, sizeof(buf));	
		ret = scanf("%s", buf);
		if(ret > 0) printf("%s\n", buf);
		//printf("222\n");
	}
	
	return 0;
}




