#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
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
	fd = open("test.txt", O_RDWR);		/* 以可写方式打开文件 */
	if(fd == -1){
		perror("fail to open");
		exit(1);
	}
	/* 建立一个内存映射，起始地址由系统为用户选择，并作为返回值返回
	* 建立的映射区的大小为打开的文件的大小
	* 访问权限为可写，属性为不更新磁盘文件 
	*/
	buf = (char *)mmap(NULL, statbuf.st_size, PROT_WRITE, MAP_PRIVATE, fd, 0);
	if(buf == MAP_FAILED){
		perror("fail to mmap");
		exit(1);
	}
	strcpy(buf, "China beijing");			/* 修改映射的文件内容 */
	if(munmap(buf, statbuf.st_size) == -1){ /* 撤销内存映射，修改的内容被丢弃 */
		perror("fail to munmap");
		exit(1);
	}
	close(fd);							/* 关闭文件 */
	return 0;
}
