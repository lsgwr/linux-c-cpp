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

	

	char buf2[30] = {0};
	read(fd, buf2+3, 11);

	
	printf("buf2 = %s\n", buf2);	
	


	int i=0;
	for(i=3; i<30; i++)
	{
		printf("%c", buf2[i]);
	}
	printf("\n");


	close(fd);


	return 0;
}
