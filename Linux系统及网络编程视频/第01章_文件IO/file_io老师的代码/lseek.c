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
	
	fd = open("./file.txt", O_RDWR);
	if(-1 == fd)
	{
		perror("open fail");
		exit(-1);
	}
	

	//ret = lseek(fd, 0, SEEK_END);
	
	ret = lseek(fd, -10, SEEK_END);
	//ret = lseek(fd, 10, SEEK_SET);
	//ret = lseek(fd, 10, SEEK_CUR);
	
	if(-1 == ret)
	{
		perror("lseek fail");
		exit(-1);
	}	
	
	//printf("ret = %d\n", ret);
	
	char buf[30] = {0};
	read(fd, buf, sizeof(buf));
	
	printf("buf = %s\n", buf);


	return 0;
}

