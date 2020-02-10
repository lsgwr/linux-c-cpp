#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
/* 新的文件权限，使所有者、组用户和其他用户具有读文件的权限 */
#define NEW_MOD S_IRUSR | S_IRGRP | S_IROTH
int main(void)
{
	int fd;
	struct stat statbuf;
	mode_t mode;
	if(chmod("test.txt", NEW_MOD) == -1){ 			/* 使用绝对权限字改变														   test.txt的权限 */
		perror("fail to change model");
		exit(1);
	}
	if(stat("test2.txt", &statbuf) == -1){ 		/* 取得文件的状态 */
		perror("fail to stat");
		exit(1);
	}
	/* 使用相对权限字改变文件权限 */
	mode = statbuf.st_mode; 						/* 取得文件权限字 */
	mode &= (~ S_IRWXU & ~ S_IRWXG & ~ S_IRWXO);	/* 关闭文件所有的权限 */
	mode |= (NEW_MOD); 								/* 打开所有用户的读权限 
													   */
	if(chmod("test2.txt", mode) == -1){ 			/* 改变文件权限 */
		perror("fail to change model");
		exit(1);
	}
	return 0;
}
