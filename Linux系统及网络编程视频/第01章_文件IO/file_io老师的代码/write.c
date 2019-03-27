#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>


int main(void)
{
	int fd = 0;


	fd = open("./file.txt", O_RDWR|O_CREAT, 0664);
	if(-1 == fd)
	{
		printf("open fail: %d\n", errno);
		return 0;
	}
	else
	{
		printf("open ok\n");
		printf("fd = %d\n", fd);
	}

	
	char buf1[] = "hello world";
	//write(fd, (void *)buf1, 11);
	
	//write(fd, (void *)buf1+1, 10);
	
	//write(fd, "hello world", 9);
	write(fd, "hello world"+1, 10);

	
	return 0;
}
