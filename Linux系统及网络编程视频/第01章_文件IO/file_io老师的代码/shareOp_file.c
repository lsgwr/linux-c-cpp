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
	int fd2 = 0;
		
	
	fd1 = open(FILE_NAME, O_RDWR|O_TRUNC|O_APPEND);
	if(-1 == fd1) print_error("1 open fail");

	
	fd2 = open(FILE_NAME, O_RDWR|O_TRUNC|O_APPEND);
	if(fd2 == -1) print_error("2 open fail");

	printf("fd1 = %d, fd2 = %d\n", fd1, fd2);	

	while(1)
	{
		write(fd2, "world\n", 6);
		sleep(1);
		write(fd1, "hello\n", 6);
	}


	
	return 0;
}

