#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
int main(void)
{
	int fd;
	char *buf;
	int i;
	struct stat statbuf;
	if(stat("test.txt", &statbuf) == -1){ /* 得到一个文件的状态信息，得到文件
											的大小 */
		perror("fail to get stat");
		exit(1);
	}
	fd = open("test.txt", O_RDONLY);        /* 以只读方式打开文件 */
	if(fd == -1){
		perror("fail to open");
		exit(1);
	}
	/* 建立一个内存映射，起始地址由系统为用户选择，并作为返回值返回
	* 建立的映射区的大小为打开的文件的大小
	* 访问权限为只读，属性为不会写到磁盘，防止对其进行写的误操作
	*/
	buf = (char *)mmap(NULL, statbuf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if(buf == MAP_FAILED){
		perror("fail to mmap");
		exit(1);
	}
	i = 0;
	while(i < statbuf.st_size){ /* 输出每一个字符，注意mmap函数不会添加’\0’结
								束符 */
		printf("%c", buf[i]);
		i++;
	}
	printf("\n");
	if(munmap(buf, statbuf.st_size) == -1){ /* 撤销内存映射 */
		perror("fail to munmap");
		exit(1);
	}
	close(fd); /* 关闭文件 */
	return 0;
}
