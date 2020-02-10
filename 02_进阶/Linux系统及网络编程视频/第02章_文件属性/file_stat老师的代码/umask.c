#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(void)
{
	int fd = 0;
	mode_t ret = 0;

	ret = umask(0); 
	printf("oldUmask = %d\n", ret);

	fd = open("./new_file.txt", O_RDWR|O_CREAT, 0777);
	if(-1 == fd)
	{
		printf("open fail\n");
		return 0;
	}
	
	ret = umask(ret);
	printf("ret = %d\n", ret);

	return 0;
}
