#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#define MAX 1024
void my_ls(char *root)
{
	DIR * dir;
	struct dirent * ptr;
	int count;
	dir = opendir(root); /* 打开目录 */
	if(dir == NULL){
		perror("fail to open dir");
		exit(1);
	}
	errno = 0;
	while((ptr = readdir(dir)) != NULL){ /* 顺序读取每一个目录项 */
		/* 跳过".."和"."两个目录 */
		if(strcmp(ptr->d_name,".") == 0 || strcmp(ptr->d_name,"..") == 0)
			continue;
		printf("%s\t", ptr->d_name); /* 打印每一个文件的文件名 */
		count++; /* 换行计数 */
		if(count %5 == 0)
			printf("\n");
	}
	if(errno != 0){ /* 如果errno是0，则说明目录中目录项已经全部读完 */
		perror("fail to read dir");
		exit(1);
	}
	closedir(dir); /* 注意一定要关闭目录 */
}
int main(int argc, char * argv[])
{
	if(argc != 2){
		printf("wrong usage\n");
		exit(1);
	}
	my_ls(argv[1]);
	return 0;
}
