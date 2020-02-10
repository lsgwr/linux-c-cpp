#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
int main(void)
{
	int fd;
	int i;
	fd = open("test.txt", O_RDWR); /* 打开一个文件，其打开方式为可写 */
	if(fd == -1){
		error("fail to open");
		exit(1);
	}
	i = 0;
	while(i < 3){
		sleep(5); 				/* 休眠5秒钟 */
		printf("hello\n");
		if(write(fd, "hello\n", 6) == -1){ /* 向文件输出一行字符串作为提示信息 
											   */
			perror("fail to write");
			exit(1);
		}
		
		if(fsync(fd) == -1){ /* 输出信息后立即进行文件同步，保证输出信息即时写回
								到磁盘上 */
			perror("fail to fsync");
			exit(1);
		}
		i++;
	}
	close(fd); /* 关闭文件 */
	return 0;
}
