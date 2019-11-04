#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> 
int main(void)
{
	int fd; 						/* 文件描述符 */
	/* 以“读写”模式打开当前目录下的test.txt文件，如果不存在则创建该文件，
	* 并且将其文件权限字设置为八进制的0700
	*/
	fd = open("test.txt",  O_RDWR | O_CREAT,  0700);
	if(fd == -1){
		perror("fail to open"); 	/* 打开文件出错，打印错误号 */
		exit(1);
	}else
		printf("open OK\n");
	close(fd); 						/* 关闭文件，有关内容见本书后面小节 */
	return 0;
}
