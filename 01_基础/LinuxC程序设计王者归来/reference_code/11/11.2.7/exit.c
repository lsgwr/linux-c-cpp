#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
int main(void)
{
	int fd;
	if((fd = open("no_such_a_file", O_RDWR)) == -1){ /* 打开一个根本不存在的
														 文件 */
		printf("fail to open file\n");
		exit(errno); /* 程序出错退出，将错误编号作为参数传递 */
	}
	return 0;
}
