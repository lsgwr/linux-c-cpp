#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(void)
{
	int fd = 0;
	mode_t ret = 0;

	
	//truncate("./new_file.txt", 10);


	fd = open("./new_file.txt", O_RDWR|O_CREAT, 0777);
	if(-1 == fd)
	{
		printf("open fail\n");
		return 0;
	}

	//ftruncate(fd, 5);
	ftruncate(fd, 20);
	

	return 0;
}
