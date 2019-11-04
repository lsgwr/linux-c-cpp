#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
int main(void)
{
	int fd;
	char *buf;
	struct stat statbuf;
	if(stat("test.txt", &statbuf) == -1){ /* 得到一个文件的状态信息，得到文件
											  的大小 */
		perror("fail to get stat");
		exit(1);
	}
	fd = open("test.txt", O_RDWR); /* 以可写方式打开文件 */
	if(fd == -1){
		perror("fail to open");
		exit(1);
	}
	/* 建立一个内存映射区，其访问权限为只读 */
	buf = (char *)mmap(NULL, statbuf.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if(buf == MAP_FAILED){
		perror("fail to mmap");
		exit(1);
	}
	printf("chang mode\n");
	/* 将映射区的访问权限改变为可读可写 */
	if(mprotect(buf, statbuf.st_size, PROT_READ | PROT_WRITE) == -1){
		perror("fail to alter permission");
		exit(1);
	}
	printf("write done\n");
	strcpy(buf, "China\n"); /* 再次写一个只读的映射区 */
	if(munmap(buf, statbuf.st_size) == -1){ /* 撤销内存映射 */
		perror("fail to munmap");
		exit(1);
	}
	close(fd); /* 关闭文件 */
	return 0;
}
