#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#define MAX 1024
/* get_file_count函数的参数是一个路径，表示目录树的根。
* 该函数返回参数指定目录下所有普通文件的数目。
*/
int get_file_count(char *root)
{
	DIR * dir;
	struct dirent * ptr;
	int total = 0;			/* 文件总数 */
	char path[MAX];
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
		if(ptr->d_type == DT_DIR){ /* 如果是目录，则递归调用get_file_count函
									数 */
			sprintf(path, "%s/%s", root, ptr->d_name);
			total += get_file_count(path);
		}
		if(ptr->d_type == DT_REG) /* 如果是普通文件，则总数递增 */
			total++;
	}
	if(errno != 0){ /* 如果errno是0，则说明目录中目录项已经全部读完 */
		perror("fail to read dir");
		exit(1);
	}
	closedir(dir); /* 注意一定要关闭目录 */
	return total; /* 返回普通文件数 */
}
int main(int argc, char * argv[])
{
	int total;
	if(argc != 2){ /* 命令行参数错误 */
		printf("wrong usage\n");
		exit(1);
	}
	total = get_file_count(argv[1]); /* 得到文件数目 */
	printf("%s has %d files\n", argv[1], total);
	return 0;
}
