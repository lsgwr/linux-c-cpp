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
	while((d_ptr = readdir(dir))!=NULL){ /* 顺序输出目录中的每个文件的文件名 */
		printf("dir name is :%s \n",d_ptr->d_name);
	}
	printf("read again\n");
	rewinddir(dir); /* 目录文件的读写位置归0 */
	while((d_ptr = readdir(dir))!=NULL){ /* 再次输出每个文件 */
		printf("dir name is :%s\n",d_ptr->d_name);
	}
	closedir(dir); /* 关闭目录 */
	return 0;
}
