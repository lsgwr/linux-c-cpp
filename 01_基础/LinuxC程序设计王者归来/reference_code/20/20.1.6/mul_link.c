#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#define MAX 1024
int main(void)
{
	int fd;
	char buf[MAX];
	int n;
	if(symlink("test.txt", "sl1") == -1){ /* 创建一个符号链接，指向test.txt文件 */
		perror("fail to create symbol link");
		exit(1);
	}
	/* 再次创建一个符号链接，指向sll。就此形成了一个符号链接链：sl2->sl1->test.txt
	* test.txt文件是目的文件，也是该符号链接链的重点 
	*/
	if(symlink("sl1","sl2") == -1){ 
		perror("fail to create symbol link");
		exit(1);
	}
	if((fd = open("sl2", O_RDWR)) == -1){ /* 打开的实际上是目的文件test.txt */
		perror("fail to open");
		exit(1);
	}
	printf("already create symbol-links\n");
	if((n = read(fd, buf, MAX)) == -1){ /* 读文件的内容 */
		perror("fail to read");
		exit(1);
	}
	buf[n] = '\0';
	printf("file content is : %s\n", buf); /* 输出结果*/
	strcat(buf, ", admin");
	if(write(fd, buf, strlen(buf)) == -1){ /* 向该文件写内容 */
		perror("fail to write");
		exit(1);
	}
	printf("done\n"); /* 输出提示信息 */
	close(fd);
	return 0;
}
