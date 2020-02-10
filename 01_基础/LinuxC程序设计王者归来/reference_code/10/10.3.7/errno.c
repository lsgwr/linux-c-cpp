#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> /* Linux系统调用的头文件 */
#include <unistd.h>
#include <errno.h> /* 错误号声明的头文件 */
int main(void)
{
	int fd;
	errno = 0; /* 错误号 */
	fd = open("/home/Linux-c/nothing.txt", O_RDWR); /* 打开一个文件 */
	if(errno == 0) /* 没有出错 */
		printf("Sucessful\n");
	else{ /* 出错则打印出错号 */
		printf("Fail to open, errno is : %d\n", errno);
		exit(1);
	}
	close(fd); /* 关闭文件 */
	return 0;
}
