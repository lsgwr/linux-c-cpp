#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
int main(void)
{
	struct stat buf;
	if(stat("./test.txt", &buf) == -1){ /* 取得文件状态信息 */
		printf("stat error\n");
		exit(0);
	}
	if((buf.st_mode & S_IRGRP) != 0) /* 测试组用户是否对该文件有读权限 */
		printf("user of the group can read\n");
	else
		printf("user of the group can not read\n"); /* 输出提示信息 */
	return 0;
}
