#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(void)
{
	DIR *dir;
	struct dirent *d_ptr;
	off_t offset;
	dir = opendir("/home/linux-c"); /* 打开目录 */
	if(dir == NULL){
		perror("fail to open dir");
		exit(1);
	}
	while((d_ptr = readdir(dir))!=NULL){ /* 输出目录中每个文件的文件名和其目录
											 项在目录文件中的偏移 */
		offset = telldir (dir); /* 得到当前的偏移位置 */
		if(offset == -1){
			perror("fail to get offset");
			exit(1);
		}
		printf("dir name is : %s offset is :%d\n", d_ptr->d_name,(int)offset); 
		/* 输出结果 */
	}
	closedir(dir);
}
