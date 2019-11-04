#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
int main(void)
{
	int fd;
	fd = creat("test.txt", 0700); /* 创建一个新文件，使用权限字为700 */
	if(fd == -1){
		perror("fail to creat");
		exit(1);
	}else
		printf("creat OK\n");      /* 输出提示信息 */
	return 0;
}
