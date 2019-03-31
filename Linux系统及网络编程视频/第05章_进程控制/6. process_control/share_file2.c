#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



int main(void)
{
	pid_t ret = 0;
	int fd = 0;
	
	fd = open("./file.txt", O_RDWR|O_CREAT, 0664);
	ret = fork();
	if(ret > 0)
	{
		write(fd, "hello\n", 6);
		printf("p, uid = %d, gid = %d\n", getuid(), getgid());
	}
	else if(ret == 0)
	{
		write(fd, "world\n", 6);
		printf("c, uid = %d, gid = %d\n", getuid(), getgid());
	}
	
	return 0;
}
