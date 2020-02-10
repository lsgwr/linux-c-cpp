#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int count(char *root)
{
	DIR *dp;
	struct dirent *item;
	int n = 0;

	dp = opendir(root);
	if (dp == NULL) {
		perror("opendir error");
		exit(1);		
		//count是次级函数，出错应返回一个自定义个错误号给调用者处理
		//这里直接调用exit退出。
	}
	while ((item = readdir(dp))) {	//遍历每一个目录项，NULL表示读完
		struct stat statbuf;
		printf("=======想想程序为什么出错？=======\n");
		/*取文件的属性， lstat防止穿透*/
		if(lstat(item->d_name, &statbuf) == -1){
			perror("lstat error");
			exit(1);
		}

		if (S_ISREG(statbuf.st_mode)) {
			n++;
		} else if (S_ISDIR(statbuf.st_mode))
			n += count(item->d_name);
	}

	closedir(dp);

	return n;
}

int main(void)
{
	int total;

	total = count("./");

	//printf("There are %d files in %s\n", total, argv[1]);
	printf("There are %d files in ./\n", total);

	return 0;
}
