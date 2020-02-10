#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
/* linux cp命令的简单实现，命令格式：cp des src
* 成功返回0，失败返回-1，失败原因保存在errno中
* argv[1] : 目标文件名des（本例使用绝对路径）
* argv[2]: 源文件名src（本例使用绝对路径）
*/
#define MAX 30
int main(int argc, char *argv[])
{
	char buf[MAX];
	int in, out; /* 输入文件和输出文件 */
	int n;
	if(argc != 3)
		exit(1);
	if((in = open(argv[2], O_RDONLY)) == -1) {/* 源文件，“只读”打开 */
		perror("fail to open");
		exit(1);
	}
	/* 目标文件，该文件不存在则创建，该文件存在则覆盖且只写打开 */
	if((out = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT)) == -1){ 
		perror("fail to open");
		exit(1);
	}
	while((n = read(in, buf, MAX)) > 0) /* 读入文件 */
		if((write(out, buf, n)) != n){ /* 实际写出字节数不等于n，写出错 */
			perror("fail to write");
			exit(1);
		}
	if(n < 0){ /* 读入出错 */
		perror("fail to read");
		exit(1);
	}
	printf("copy done\n"); /* 输出提示信息 */
	close(in);				/* 关闭两个文件 */
	close(out);
	return 0;
}
