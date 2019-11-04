#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main(void)
{
	int fd;
	char *p = "linux ok\n"; 					/* 测试使用的字符串 */
	fd = open("test.txt", O_WRONLY | O_TRUNC); /* 该文件只写打开，并且将文件
												截短为0 */
	if(fd == -1){
		perror("fail to open");
		exit(1);
	}
	if(write(fd, p, strlen(p)) == -1){ /* 输入新内容，该内容会完全取代旧的内容 */
		perror("fail to write");
		exit(1);
	}
	close(fd); /* 关闭文件 */
	return 0;
}
