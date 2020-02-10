#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
	int fd;
	char *str = "hello dup2\n";

	//write(STDOUT_FILENO, str, strlen(str));

	fd = open("test", O_WRONLY|O_TRUNC|O_CREAT, 0644);
	if(fd < 0){
		perror("open test1 error");
		exit(1);
	}
	dup2(STDOUT_FILENO, fd);		
	//dup2(fd, STDOUT_FILENO);

	close(fd);

	//做文件关闭之前同样的事。
	int n = write(STDOUT_FILENO, str, strlen(str));		
	//int n = write(fd, str, strlen(str));		
	printf("--------|%d\n", n);

	return 0;
}
