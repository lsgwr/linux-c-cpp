#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>


int main(void)
{
	int fd = 0;


	fd = open("./file.txt", O_RDWR);
	if(-1 == fd)
	{
		printf("open fail: %d\n", errno);
		return 0;
	}

	/* 模拟dup */
	//close(1);
	//dup(fd);
	
	//close(1);
	//fcntl(fd, F_DUPFD, 0);

	
	/* 模拟dup2 */
	//dup2(fd, 1);
	close(1);
	fcntl(fd, F_DUPFD, 1);
	
	printf("hello world!!\n");	
	
	
	return 0;
}
