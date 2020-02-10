#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(void)
{
	int fd = 0;
	mode_t ret = 0;

	


	fd = open("./hole_file.txt", O_RDWR|O_CREAT, 0664);
	if(-1 == fd)
	{
		printf("open fail\n");
		return 0;
	}

	//ftruncate(fd, 8000);
	
	lseek(fd, 8000, SEEK_SET);
	
	write(fd, "hello", 5);	


	return 0;
}
