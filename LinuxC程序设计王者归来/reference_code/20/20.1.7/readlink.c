#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define MAX 1024
int main(void)
{
	char buf[MAX];
	int fd,n;
	if(symlink("test.txt", "sl1") == -1){ /* 创建第	一个符号链接，指向test.txt文件 */
		perror("fail to create symbol-link");
		exit(1);
	}
	if(symlink("sl1", "sl2") == -1){ /* 创建第二个符号链接，指向符号链接sl2 */
		perror("fail to create symbol-link");
		exit(1);
	}
	if((n=readlink("sl1", buf, MAX)) == -1){ /* 读取sl1的目的文件test.txt的路径 */
		perror("fail to read symbol-link");
		exit(1);
	}
	buf[n]='\0';
	printf("%s\n", buf); /* 输出链接信息 */
	if((n=readlink("sl2", buf, MAX)) == -1){ /* 读取sl2的目的文件符号链接sl1的路径 
											 */
		perror("fail to read symbol-link");
		exit(1);
	}
	buf[n]='\0';
	printf("%s\n", buf); /* 输出链接信息 */
	return 0;
}
