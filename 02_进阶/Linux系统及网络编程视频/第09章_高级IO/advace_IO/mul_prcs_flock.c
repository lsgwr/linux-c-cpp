#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
//#include "file_lock.h"
#include <sys/file.h>


void print_err(char *str, int line, int err_no)
{
        printf("%d, %s: %s\n", line, str, strerror(err_no));
        exit(-1);
}

int main(void)
{	
	int fd = 0;
	int ret = 0;
	

	ret = fork();
	if(ret > 0)
	{
		fd = open("./file", O_RDWR|O_CREAT|O_TRUNC|O_APPEND, 0664);
		if(fd == -1) print_err("./file", __LINE__, errno);
		
		while(1)
		{
			flock(fd, LOCK_SH);
			write(fd, "hello ", 6);
			write(fd, "world\n", 6);
			flock(fd, LOCK_UN);
		}
	}	
	else if(ret == 0)
	{	
		fd = open("./file", O_RDWR|O_CREAT|O_TRUNC|O_APPEND, 0664);
		if(fd == -1) print_err("./file", __LINE__, errno);

		while(1)
		{
			flock(fd, LOCK_SH);
			write(fd, "hello ", 6);
			write(fd, "world\n", 6);
			flock(fd, LOCK_UN);
		}
	}	
	
	return 0;
}	
	
	
