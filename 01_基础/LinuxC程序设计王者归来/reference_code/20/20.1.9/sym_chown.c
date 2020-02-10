#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
int main(void)
{
	struct stat statbuf;
	printf("before changing\n"); /* 输出提示信息 */
	if(stat("test.txt", &statbuf) == -1){ /* 得到目的文件的状态信息 */
		perror("fail to get status");
		exit(1);
	}
	printf("the owner of test.txt is : %u\n", (unsigned int)statbuf.st_uid);
	printf("the group of test.txt is : %u\n", (unsigned int)statbuf.st_gid);
	if(lstat("sl", &statbuf) == -1){ /* 使用lstat函数得到符号链接的状态信息 */
		perror("fail to get status");
		exit(1);
	}
	printf("the owner of sl is : %u\n", (unsigned int)statbuf.st_uid);
	printf("the group of sl is : %u\n", (unsigned int)statbuf.st_gid);
	if(chown("sl", 0, -1) == -1){ /* 改变目的文件的所有者 */
		perror("fail to change owner");
		exit(1);
	}
	printf("after changing\n"); /* 输出提示信息 */
	if(stat("test.txt", &statbuf) == -1){ /* 再次得到目的文件的文件状态信息 */
		perror("fail to get status");
		exit(1);
	}
	printf("the owner of test.txt is : %u\n", (unsigned int)statbuf.st_uid);
	printf("the group of test.txt is : %u\n", (unsigned int)statbuf.st_gid);
	if(lstat("sl", &statbuf) == -1){ /* 使用lstat函数得到符号链接本身的文件状
									态信息 */
		perror("fail to get status");
		exit(1);
	}
	printf("the owner of sl is : %u\n", (unsigned int)statbuf.st_uid);
	printf("the group of sl is : %u\n", (unsigned int)statbuf.st_gid);
	return 0;
}
