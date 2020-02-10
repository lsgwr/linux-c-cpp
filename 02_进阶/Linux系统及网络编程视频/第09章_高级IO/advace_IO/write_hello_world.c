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
#include "file_lock.h"


void print_err(char *str, int line, int err_no)
{
        printf("%d, %s: %s\n", line, str, strerror(err_no));
        exit(-1);
}

int main(void)
{	
	int fd = 0;
	int ret = 0;
	
	fd = open("./file", O_RDWR|O_CREAT|O_TRUNC, 0664);
	if(fd == -1) print_err("./file", __LINE__, errno);

	ret = fork();
	if(ret > 0)
	{
		
		while(1)
		{
			SET_WRFLCK_W(fd, SEEK_SET, 0, 0);
			write(fd, "hello ", 6);
			write(fd, "world\n", 6);
			UNLCK(fd, SEEK_SET, 0, 0);
		}
	}	
	else if(ret == 0)
	{	
		while(1)
		{
			SET_WRFLCK_W(fd, SEEK_SET, 0, 0);
			write(fd, "hello ", 6);
			write(fd, "world\n", 6);
			UNLCK(fd, SEEK_SET, 0, 0);
		}
	}	
	
	return 0;
}	
	
	
