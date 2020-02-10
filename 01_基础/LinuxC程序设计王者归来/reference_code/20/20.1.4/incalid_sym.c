#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
int main(void)
{
	int fd;
	if(symlink("nothing.txt", "invalid_link")==-1){/*创建一个符号链接，注意链
												   接的目的文件是不存在的 */
		perror("fail to create symbol link");
		exit(1);
	}
	printf("already create a symbol-link\n"); /* 输出提示信息 */
	if((fd = open("invalid_link", O_RDWR)) == -1){ /* 打开刚刚创建的符号链接 */
		perror("fail to open");
		exit(1);
	}
	printf("should not be here\n"); /* 打开目的文件失败，程序直接调用exit函数
									退出，不会执行到这里 */
	return 0;
}
