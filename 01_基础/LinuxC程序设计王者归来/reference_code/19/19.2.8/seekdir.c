#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
int main(void)
{
	DIR *dir;
	struct dirent * d_ptr;
	dir=opendir("./"); /* 打开目录 */
	if(dir == NULL){
		perror("fail to open dir");
		exit(1);
	}
	seekdir(dir,1117558374); /* 根据上例的输出，可知“.”和“..”两个目录项共占24个字节	*/
	/* 输出跨过“.”和“..”后的目录项 */
	while((d_ptr = readdir(dir))!=NULL){
		printf("dir name is :%s \n",d_ptr->d_name);
	}
	closedir(dir); /* 关闭目录 */
	return 0;
}
