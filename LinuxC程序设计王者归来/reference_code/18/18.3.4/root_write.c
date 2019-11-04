#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define MAX 1024
int main(int argc, char *argv[ ])
{
	int sfd, dfd;
	struct stat statbuf;
	char buf[MAX];
	int n;
	if(stat(argv[0], &statbuf) == -1){ /* 取得执行程序文件的状态信息 */
		perror("fail to stat");
		exit(1);
	}
	if(statbuf.st_mode & S_ISUID != 0) /* 测试组用户是否设置了“设置用户ID”位 
										   */
		printf("set user id\n");
	else{
		printf("can’t write to root.txt\n");
		exit(1);
	}
	if((sfd = open("test.txt", O_RDONLY)) == -1){ /* 打开源文件，里面有需要写到
												  root.txt中的内容 */
		perror("fail to open");
		exit(1);
	}
	if((dfd = open("root.txt", O_WRONLY)) == -1){ /* 打开root.txt文件 */
		perror("fail to open");
		exit(1);
	}
	while(n = read(sfd, buf, sizeof(char)) >0){ /* 将sfd文件中的内
													容写到dfd文件中去 */
		if(write(dfd, buf ,sizeof(char)) == -1){
			perror("fail to write");
			exit(1);
		}
	}
	if(n < 0){ /* 如果因为read函数返回-1而跳出循环，则说明read函数出错 */
		perror("fail to read");
		exit(1);
	}
	printf("done\n"); /* 输出提示信息 */
	return 0;
}
