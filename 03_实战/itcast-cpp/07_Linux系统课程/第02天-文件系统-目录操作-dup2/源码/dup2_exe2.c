/*
 *如果使用dup2给一个文件制定了两个描述符的时候
 *一个文件描述符关闭，依然能使用dup2的新文件描述符对该文件读写
 */
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
	int fd, fd2;
	char *str = "use fd write in\n";
	char *str2 = "use ====fd2==== write\n";

	fd = open("test", O_WRONLY|O_TRUNC|O_CREAT, 0644);  //3
	if(fd < 0){
		perror("open test error");
		exit(1);
	}
	fd2 = open("test", O_WRONLY);  //4

	dup2(fd, fd2);

	write(fd, str, strlen(str));
	close(fd);

	printf("----------------done close(fd)--------------\n");

	int ret = write(fd2, str2, strlen(str2));
	if(ret == -1){
		perror("write fd2 error");
		exit(1);
	}

	close(fd2);

	return 0;
}
