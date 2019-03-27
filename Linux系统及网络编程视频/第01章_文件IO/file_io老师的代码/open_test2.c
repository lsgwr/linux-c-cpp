#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(void)
{
	int fd = 0;
	int ret = 0;

	fd = open("./file.txt", O_RDWR);
	//fd = open("./file.txt", O_RDWR|O_APPEND);
	//fd = open("./file.txt", O_RDWR|O_TRUNC);
	//fd = open("./file.txt", O_RDONLY);
	//fd = open("./file.txt", O_WRONLY);
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
	ret = write(fd, (void *)buf1, 11);
	if(ret == -1)
	{
		printf("write fail\n");
	}


	lseek(fd, 0, SEEK_SET);

	char buf2[30] = {0};
	ret = read(fd, buf2, sizeof(buf2));
	if(-1 == ret)
	{
		printf("read fail\n");
	}

	printf("buf2 = %s\n", buf2);	
	
	
	close(fd);
	
	return 0;
}
