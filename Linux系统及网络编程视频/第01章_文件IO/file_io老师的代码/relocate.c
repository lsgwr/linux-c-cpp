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
	
	fd1 = open(FILE_NAME, O_RDWR|O_TRUNC);
	if(-1 == fd1) print_error("1 open fail");

	//close(1);
	//dup(fd1);
	
	dup2(fd1, 1);
	

	//printf("fd2 = %d\n", fd2);
	
	printf("hello world\n");	

	
	return 0;
}
