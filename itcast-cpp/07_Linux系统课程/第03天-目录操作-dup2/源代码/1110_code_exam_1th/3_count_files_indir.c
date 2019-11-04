#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int count(char *root)
{
	DIR *dp;
	struct dirent *item;
	int n = 0;  char path[1024];

	dp = opendir(root);             //打开目录
	if (dp == NULL) {
		perror("----opendir error");
		exit(1);		
	}
	while ((item = readdir(dp))) {	//遍历每一个目录项，NULL表示读完
		struct stat statbuf;

        if (strcmp(item->d_name, ".") == 0 || strcmp(item->d_name, "..") == 0)
            continue;

        sprintf(path, "%s/%s", root, item->d_name);//将子目录和当前工作目录拼接成一个完整文件访问路径

		/*取文件的属性， lstat防止穿透*/
		if (lstat(path, &statbuf) == -1) {
			perror("lstat error");
			exit(1);
		}

		if (S_ISREG(statbuf.st_mode)) {
			n++;
		} else if (S_ISDIR(statbuf.st_mode)) {
			n += count(path);       //递归调用该函数
        }
	}

	closedir(dp);

	return n;
}

int main(int argc, char *argv[])
{
	int total = 0;

    if (argc == 1) {
	    total = count(".");
	    printf("There are %d files in ./\n", total);
    } else if (argv[1]) {
        total = count(argv[1]);
	    printf("There are %d files in %s\n", total, argv[1]);
    }

	return 0;
}
