#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#define MAX 1024
int main(void)
{
	int fd;
	off_t off;
	char buf[MAX];
	fd = open("test.txt", O_RDWR); /* 打开一个文件 */
	if(fd == -1){
		perror("fail to open");
		exit(1);
	}
	printf("before reading\n"); 	/* 输出提示信息 */
	off = lseek(fd, 0, SEEK_CUR);	/* 调用lseek函数得到当前文件的读写位置 */
	if(off == -1){
		perror("fail to lseek");
		exit(1);
	}
	printf("the offset is : %d\n", (int)off); /* 输出提示信息 */
	if(read(fd,buf, 5 ) == -1){ /* 读取5个字节的文件内容 */
		perror("fail ot read");
		exit(1);
	}
	printf("after reading\n");   /* 输出提示信息 */
	off = lseek(fd, 0, SEEK_CUR); /* 再次调用lseek函数得到当前文件的读写位置 */
	if(off == -1){
		perror("fail to lseek");
		exit(errno);
	}
	printf("the offset is : %d\n", (int)off); /* 输出结果 */
	close(fd);								/* 关闭文件 */
	return 0;
}
