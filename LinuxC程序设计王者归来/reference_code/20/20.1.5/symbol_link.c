#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#define MAX 1024
int main(void)
{
	int fd,n;
	char buf[MAX];
	if(symlink("test.txt", "sym_link") == -1){ /* 创建一个符号链接，目的文件是test.txt */
		perror("fail to create symbol link");
		exit(1);
	}
	printf("already create a symbol-link\n"); /* 输出提示信息 */
	if((fd = open("sym_link", O_RDWR)) == -1){ /* 通过符号链接打开该目的文
													件 */
		perror("fail to open");
		exit(1);
	}
	if((n = read(fd, buf, MAX)) == -1){ /* 读目的文件的内容 */
		perror("fail to read");
		exit(1);
	}
	buf[n] = '\0';
	printf("file content is : %s\n", buf); /* 打印目的文件的内容 */
	strcat(buf, ", admin");
	if(write(fd, buf, strlen(buf)) == -1){ /* 向目的文件输出 */
		perror("fail to write");
		exit(1);
	}
	printf("done\n"); /* 输出提示信息 */
	close(fd);
	return 0;
}
