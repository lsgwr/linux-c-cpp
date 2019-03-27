#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define FILE_NAME "./file.txt"


void print_error(char * str)
{
	perror(str);
	exit(-1);
}


int main(void)
{
	int fd1 = 0;
	
	fd1 = open(FILE_NAME, O_RDWR|O_TRUNC|O_APPEND);
	if(-1 == fd1) print_error("1 open fail");

	
	printf("fd1 = %d\n", fd1);	

	while(1)
	{
		write(fd1, "hello\n", 6);
		sleep(1);
	}


	
	return 0;
}

