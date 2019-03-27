#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>




int main(void)
{
	int fd = 0;
	int ret = 0;
	
	fd = open("./file.txt", O_RDONLY);
	if(-1 == fd)
	{
		perror("open fail");
		exit(-1);
	}
	
	ret = write(fd, "hello world!!!", 14);
	if(-1 == ret)
	{
		perror("write fail");
		exit(-1);
	}
	

	return 0;
}

