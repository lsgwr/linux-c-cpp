#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
int main(void)
{
	int fd;
	int len = strlen("hello world\n"); /* 测试用的字符串 */
	char *p = "hello world\n";
	if((fd = open("test.txt", O_RDWR | O_CREAT)) == -1){ /* 打开一个文件，如果文件不存在则创建 */
		perror("fail to open");
		exit(1);
	}
	while(1){
		if(write(fd, p, len) == -1){ /* 死循环，不停向文件输出信息 */
			perror("fail to write");
			exit(1);
		}
		sleep(1);
	}
	close(fd); /* 关闭文件 */
	return 0;
}
