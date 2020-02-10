#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
/* 屏蔽所有者、组用户和其他用户的“可读权限” */
#define MASK S_IRUSR | S_IRGRP | S_IROTH
int main(void)
{
	int fd;
	mode_t mask;
	mask = umask(MASK); /* 改变权限屏蔽字，并将原来的屏蔽字保存 */
	printf("the original mask is %x\n", (unsigned int )mask);
					/*打印旧的权限屏蔽字 */
	/* 使新文件的所有者、组用户和其他用户的权限全部被设置 */
	if((fd = open("test.txt", O_CREAT, 0777)) == -1){
		perror("fail to create");
		exit(1);
	}
	close(fd);     /* 关闭文件 */
	return 0;      /* 程序退出，不将umask屏蔽字更改回去，检查其是否影响其所在的
					shell环境 */
}
