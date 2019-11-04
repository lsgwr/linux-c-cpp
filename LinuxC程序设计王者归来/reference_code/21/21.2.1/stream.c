#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
int main(void)
{
	FILE *fp;
	int fd;
	if( (fp = fopen("test.txt", "w+")) == NULL){ /* 以读写方式打开流 */
		perror("fail to open");
		exit(1);
	}
	fprintf(fp, "hello world\n"); /* 向该流输出一段信息，这段信息会反馈到文件上 */
	fclose(fp);					 /* 关闭流 */
	if( (fd = open("test.txt", O_RDWR)) == -1){ /* 以读写的方式打开文件 */
		perror("fail to open");
		exit(1);
	}
	if((fp = fdopen(fd, "a")) == NULL){ /* 在打开的文件上打开一个流 */
		perror("fail to open stream");
		exit(1);
	}
	fprintf(fp,"hello world again\n");
	fclose(fp); 				/* 关闭流，文件也被关闭 */
	return 0;
}
