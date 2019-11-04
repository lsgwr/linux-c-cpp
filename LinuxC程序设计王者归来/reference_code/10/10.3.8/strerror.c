#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>		/* Linux系统调用的头文件 */
#include <unistd.h>
#include <errno.h>		/* 错误号声明的头文件 */
#include <string.h>
int main()
{
	int fd;
	errno = 0;			/* 错误号 */
	fd = open("/home/admin/test.txt", O_RDWR); /* 打开一个文件 */
	if(errno == 0)		/* 没有出错 */
		printf("Sucessful\n");
	else{				/* 根据出错号输出出错信息 */
		int err = errno;						/* 出错号 */
		printf("Fail : the reason is : %s\n",  strerror(err));
												/* 输出出错信息 */
	}
	close(fd);			/* 关闭文件 */
	return 0;
}
