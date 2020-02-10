#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(void)
{
	int fd = 0;

	fd = open("./file.txt", O_RDWR);
	if(-1 == fd)
	{
		printf("open fail\n");
		return 0;
	}
	else
	{
		printf("open ok\n");
	}

	
	char buf1[] = "hello world";
	write(fd, (void *)buf1, 11);

	lseek(fd, 0, SEEK_SET);

	char buf2[30] = {0};
	read(fd, buf2, sizeof(buf2));
	

	printf("buf2 = %s\n", buf2);	
	
	
	close(fd);
	
	return 0;
}
