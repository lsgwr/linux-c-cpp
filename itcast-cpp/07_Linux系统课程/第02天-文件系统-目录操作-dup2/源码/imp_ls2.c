#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
    DIR *dp;
	struct dirent *item;
	int count = 0;

    if (argc == 1) {
        dp = opendir(".");		//ls是查看当前目录的内容
        if(dp == NULL){
            perror("opendir error");
            exit(1);
        }
    } else if (argc == 2) {
        dp = opendir(argv[1]);		//ls是查看当前目录的内容
        if(dp == NULL){
            perror("opendir error");
            exit(1);
        }
    }

	//读目录项，把目录项的d_name打印
	while((item = readdir(dp))){		//item == NULL读完
		if(item->d_name[0] != '.'){
			printf("%-10s%c", item->d_name, ++count % 5 ? '\t' : '\n');	
		}
	}
	putchar('\n');

	closedir(dp);

	return 0;
}
