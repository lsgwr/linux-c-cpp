#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{
	int fd, save_fd;
	char msg[] = "It's just a test for dup2!\n";

	fd = open("test", O_RDWR|O_CREAT|O_TRUNC, 0644);	//<fcntl.h>
	if(fd < 0){
		perror("open error");
		exit(1);
	}
	save_fd = dup(STDOUT_FILENO);			//STDOUT_FILENO <unistd.h>
	printf("save_fd = %d\n", save_fd);

#if 0
	dup2(STDOUT_FILENO, fd);
	write(fd, msg, strlen(msg));
#else
	dup2(fd, STDOUT_FILENO);
	puts(msg);											
	write(fd, msg, strlen(msg));//???
#endif

	close(fd);

	return 0;
}
