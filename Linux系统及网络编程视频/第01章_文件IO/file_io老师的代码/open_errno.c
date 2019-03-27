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
	//fd = open("./file.txt", O_RDWR|O_CREAT|O_EXCL, 0664);
	if(-1 == fd)
	{
		printf("open fail: %d\n", errno);
		perror("open fail");
		return 0;
	}
	else
	{
		printf("open ok\n");
		printf("fd = %d\n", fd);
	}

	
	char buf1[] = "hello world";
	write(fd, (void *)buf1, 11);

	lseek(fd, SEEK_SET, 0);

	char buf2[30] = {0};
	read(fd, buf2, sizeof(buf2));
	

	printf("buf2 = %s\n", buf2);	
	close(fd);

	return 0;
}
