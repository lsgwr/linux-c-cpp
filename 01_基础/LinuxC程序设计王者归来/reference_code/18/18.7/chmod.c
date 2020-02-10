#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
int main(void)
{
	struct stat statbuf;
	if(stat("test.txt", &statbuf) == -1){ /* 为改变所有者前文件的状态 */
		perror("fail to get status");
		exit(1);	
	}
	printf("before changing owner\n"); /* 打印文件的所有者用户ID和组ID */
	printf("the owner of test.txt is : %d\n", (unsigned int)statbuf.st_uid);
	printf("the group of test.txt is : %d\n", (unsigned int)statbuf.st_gid);
	printf("\n");
	if(chown("test.txt", 0, -1) == -1){ /* 将文件的所有者修改为根用户，不改变组
										    用户ID */
		perror("fail to change owner");
		exit(1);
	}
	if(stat("test.txt", &statbuf) == -1){ /* 再次取得文件的状态信息 */
		perror("fail to get status");
		exit(1);
	}
	printf("after changing owner\n");
	printf("the owner of test.txt is : %d\n", (unsigned int)statbuf.st_uid); 	/* 输出结果 */
	printf("the group of test.txt is : %d\n", (unsigned int)statbuf.st_gid);
	printf("\n");
	if(chown("test.txt", 100, -1) == -1){ /* 将文件的所有者修改为一个根本不存
											   在的用户 */
		perror("fail to change owner");
		exit(1);
	}
	if(stat("test.txt", &statbuf) == -1){ /* 得到文件状态信息 */
		perror("fail to get status");
		exit(1);
	}
	printf("nonexsit owner\n");
	printf("the owner of test.txt is : %d\n", (unsigned int)statbuf.st_uid); 	/* 输出结果 */
	printf("the group of test.txt is : %d\n", (unsigned int)statbuf.st_gid);
	return 0;
}
