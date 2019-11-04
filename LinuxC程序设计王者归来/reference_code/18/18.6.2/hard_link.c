#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
/* 缓冲区的大小 */
#define MAX 1024
int main(void)
{
	int fd;
	struct stat statbuf;
	char buf[MAX];
	int n;
	if(stat("test.txt", &statbuf) == -1){ /* 得到目标文件的状态 */
		perror("fail to get status");
		exit(1);
	}
	/* 打印文件的链接数 */
	printf("test.txt, the number of links is : %d\n", statbuf.st_nlink);
	/* 当前目录下创建一个叫做test2.txt的文件，该文件和test.txt共用一个i结点 */
	if(link("test.txt", "test2.txt") == -1){
		perror("fail to link");
		exit(1);
	}
	/* 再次取得test.txt文件的状态，其链接数已经更新 */
	if(stat("test.txt", &statbuf) == -1){
		perror("fail to get status");
		exit(1);
	}
	printf("test.txt, the number of links is : %d\n", statbuf.st_nlink);
	/* 得到test2.txt文件的状态，这个状态结构实际上是文件test.txt的 */
	if(stat("test2.txt", &statbuf) == -1){
		perror("fail to get status");
		exit(1);
	}
	printf("test2.txt, the number of links is : %d\n", statbuf.st_nlink);
	printf("\n");
	if((fd = open("test.txt", O_RDWR)) == -1){ /* 打开文件test.txt */
		perror("fail to open");
		exit(1);
	}
	strcpy(buf, "hello world"); /* 复制字符串 */
	if((n = write(fd, buf, strlen(buf))) == -1){ /* 向文件中输出字符串"hello 
	world" */
		perror("fail to write");
		exit(1);
	}
	close(fd); /* 关闭文件，输出的字符串写入到磁盘文件中 */
	if((fd = open("test2.txt", O_RDWR)) == -1){ /* 打开test2.txt文件 */
		perror("fail to open");
		exit(1);
	}
	if((n = read(fd, buf, n)) == -1){ /* 读该文件的内容 */
		perror("fail to read");
		exit(1);
	}
	buf[n] = '\0'; /* 添加字符串结束标志，便于打印 */
	printf("content of test2.txt is : %s\n", buf); /* 输出test2.txt文件中
													    的内容 */
	close(fd);
	/* 删除test2.txt的目录项，但是其磁盘文件没有受到影响，
	* 仍可以通过另一个链接test.txt引用该文件 
	*/
	if(unlink("test2.txt") == -1){
		perror("fail to unlink");
		exit(1);
	}
	if(stat("test.txt", &statbuf) == -1){ /* 得到test.txt文件的状态 */
		perror("fail to get status");
		exit(1);
	}
	printf("test.txt, the number of links is : %d\n", statbuf.st_nlink); 
	/* 打印该文件链接计数 */
	/* 打开test.txt文件，这样做可以避免该文件被系统删除 */
	if((fd = open("test.txt", O_RDWR)) == -1){
		perror("fail to open");
		exit(1);
	}
	if(unlink("test.txt") == -1){ /* 现在该文件的引用计数为0了 */
		perror("fail to unlink");
		exit(1);
	}
	if(fstat(fd, &statbuf) == -1){ /* 得到文件的状态 */
		perror("fail to get status");
		exit(1);
	}
	printf("test.txt, the number of links is : %d\n", statbuf.st_nlink);
	printf("\n");
	/* 由于文件仍然打开，所有该文件仍可以应用 */
	if((n = read(fd, buf, n)) == -1){
		perror("fail to read");
		exit(1);
	}
	buf[n] = '\0';
	printf("content of test.txt is : %s\n", buf); /* 输出结果 */
	close(fd);										/* 关闭文件 */
	return 0;
}
