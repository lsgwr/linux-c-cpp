#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



int main(void)
{
	pid_t ret = 0;
	int fd = 0;
	
	ret = fork();
	if(ret > 0)
	{
		fd = open("./file.txt", O_RDWR|O_CREAT|O_APPEND, 0664);
		
		write(fd, "hello\n", 6);
	}
	else if(ret == 0)
	{
		fd = open("./file.txt", O_RDWR|O_CREAT|O_APPEND, 0664);
		
		write(fd, "world\n", 6);
	}
	
	return 0;
}
