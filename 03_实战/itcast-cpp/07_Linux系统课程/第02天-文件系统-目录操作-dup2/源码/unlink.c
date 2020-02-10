#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	int fd;

	char *p = "It's a test for unlink\n";

	if((fd = open("temp.txt", O_RDWR|O_TRUNC|O_CREAT, 0664)) == -1){
		perror("open error");
		exit(1);
	}
	unlink("temp.txt");

	write(fd, p, strlen(p));
	dup2(fd, STDOUT_FILENO);
	printf("I am printf\n");

    p[0] = 'H';

	close(fd);

	return 0;
}
