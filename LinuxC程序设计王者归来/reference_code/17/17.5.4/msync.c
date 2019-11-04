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
	char *p;
	int i;
	struct stat statbuf;
	if(stat("test.txt", &statbuf) == -1){ /* 得到一个文件的状态信息，得到文件
											   的大小 */
		perror("fail to get stat");
		exit(1);
	}
	fd = open("test.txt", O_RDWR|O_APPEND); /* 以可写方式打开文件 */
	if(fd == -1){
		perror("fail to open");
		exit(1);
	}
	/* 建立一个内存映射，起始地址由系统为用户选择，并作为返回值返回
	* 建立的映射区的大小为打开的文件的大小，测试的test.txt文件为36个字节。
	* 访问权限为可写，属性为更新磁盘文件 
	*/
	buf = (char *)mmap(NULL, statbuf.st_size, PROT_WRITE, MAP_SHARED, fd, 0);
	if(buf == MAP_FAILED){
		perror("fail to mmap");
		exit(1);
	}
	i = 0;
	p = buf ;
	while(i < 3){
		sleep(3);
		/* 每次输出一行字符串hello world，需要使用memcpy函数而不使用strcpy函数
		* strcpy函数会每次添加一个'\0'结束符
		*/
		printf("hello world\n");
		memcpy(p, "hello world\n", 12);
		i++;
		p += 12; /* 下一次的复制起始地址后移 */
		if(msync(buf, 18, MS_SYNC) == -1){ /* 将映射区的内容同步到磁盘文件上 */
			perror("fail to msync");
			exit(1);
		}
	}
	if(munmap(buf, statbuf.st_size) == -1){ /* 撤销内存映射 */
		perror("fail to munmap");
		exit(1);
	}
	close(fd); /* 关闭文件 */
	return 0;
}
