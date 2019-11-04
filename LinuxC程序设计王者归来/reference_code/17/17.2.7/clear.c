#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
int main(void)
{
	int fd;
	fd = open("test.txt",O_WRONLY); /* 需要将文件截短，该文件的打开方式必须可
										  写 */
	if(fd == -1){
		perror("fail to open");
		exit(1);
	}
	if(ftruncate(fd, 0) == -1){ /* 将原文件截短为0，文件内容不可访问 */
		perror("fail to truncate");
		exit(1);
	}
	close(fd); /* 关闭文件 */
	return 0;
}
