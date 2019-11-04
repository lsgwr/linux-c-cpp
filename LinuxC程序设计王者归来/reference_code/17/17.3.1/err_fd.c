#include <unistd.h>
int first_avail_fd()
{
	int fd;
	fd = dup(0); /* 复制任意一个已知的打开文件，标准输入几乎所有的进程都要打开 */
	close(fd);
	/* fd返回了当前第一个可用的文件描述符，但是它被测试文件占用了，关闭测试文件使它再次变为可用 */
	return fd;
}
