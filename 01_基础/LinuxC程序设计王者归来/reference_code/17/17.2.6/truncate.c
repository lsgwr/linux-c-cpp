#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define MAX 32
int main(int argc, char *argv[ ])
{
	int fd;
	int len;
	int rest;
	int i;
	char buf[MAX];
	if(argc != 3){ /* 根据命令行参数设置扩展后的文件字节数和需要填充的字节数 */
		len = MAX;
		rest = 0;
	}else{
		len = atoi(argv[1]);
		rest = atoi(argv[2]);
	}
	if(truncate("test.txt", len) == -1){ /* 截短操作，将文件拓展为指定字节数 */
		perror("fail to truncate");
		exit(1);
	}
	/* 添加写方式打开文件，每次写的内容会自动添加到文件的结尾 */
	fd = open("test.txt", O_RDWR | O_APPEND);
	if(fd == -1){
		perror("fail to open");
		exit(1);
	}
	i = 0;
	while(i < rest){ /* 设置填充内容，余下的文件内容填充为字符‘0’ */
		buf[i] = '0';
		i++;
	}
	if(write(fd, buf, rest) == -1){ /* 填充文件 */
		perror("fail to write");
		exit(1);
	}
	close(fd); /* 关闭文件 */
	return 0;
}
