#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h> /* Linux系统调用的头文件 */
#include <errno.h>		/* 错误号声明的头文件 */
#include <string.h>
int main()
{
	int fd;
	errno = 0;		/* 错误号 */
	fd = open("/home/admin/test.txt", O_RDWR); /* 打开一个文件 */
	if(fd == -1){	/* 打开文件常出错 */
		perror("fail to open");	 /* 使用perror函数输出出错信息 */
		exit(1);
	}
	close(fd);					 /* 关闭文件 */
	return 0;
}
