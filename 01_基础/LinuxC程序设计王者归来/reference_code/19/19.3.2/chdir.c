#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
int main(void)
{
	int fd;
	char *p = "hello world\n"; /* 测试用的字符串 */
	if(chdir("./tmp") == -1){ /* 改变进程的工作目录 */
		perror("fail to change dir");
		exit(1);
	}
	printf("change dir successfully\n"); /* 输出提示信息 */
	if((fd = open("test.txt", O_CREAT | O_RDWR)) == -1){ /* 创建一个文件，
												该文件创建在修改后的目录 */
		perror("fail to open");
		exit(1);
	}
	if(write(fd, p, strlen(p)) == -1){ /* 向该文件中输出内容 */
		perror("fail to write");
		exit(1);
	}
	close(fd); /* 关闭文件 */
	return 0;
}
