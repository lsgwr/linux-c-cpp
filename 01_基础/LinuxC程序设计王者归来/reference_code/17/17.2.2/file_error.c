#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
int main(void)
{
	int fd;
	fd = open("no_such_file", O_RDONLY); /* 尝试打开一个不存在的文件 */
	if(fd == -1)
		perror("fail to open");
	else
		close(fd);
	fd = open("denied", O_WRONLY);		/* 以权限不允许的方式打开文件 */
	if(fd == -1)
		perror("fail to open");
	else
		close(fd); /* 关闭打开的文件 */
	return 0;
}
