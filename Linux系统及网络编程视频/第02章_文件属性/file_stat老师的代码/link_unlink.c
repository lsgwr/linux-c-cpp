#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{


	//link("./file.txt", "../file1.txt");

	//unlink("./file1.txt");



	/* 使用unlink实现临时文件 */
	int fd = open("./file.txt", O_RDWR|O_CREAT, 0664);
	if(-1 == fd)
	{
		perror("open fail");
		exit(-1);
	}
	
	unlink("./file.txt");
	
	write(fd, "hello world\n", 12);

	lseek(fd, 0, SEEK_SET);

	char buf[30] = {0};
	read(fd, buf, sizeof(buf));

	printf("buf = %s\n", buf);

	return 0;
}
