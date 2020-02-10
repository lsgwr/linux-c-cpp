#include <unistd.h>
int first_avail_fd()
{
	int fd;
	/* 打开一个肯定存在的文件，open函数会返回第一个可用的文件描述符 */
	fd = open("test.txt",  O_RDONLY);
	close(fd); /* 关闭该文件，使第一个可用文件描述符再次变为可用 */
	return fd;
}
