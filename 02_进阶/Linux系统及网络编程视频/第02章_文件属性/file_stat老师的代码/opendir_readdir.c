#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <dirent.h>
#include <errno.h>

int main(void)
{
	DIR *dirp = NULL;

	dirp = opendir(".");	
	if(NULL == dirp)
	{
		perror("opendir fail");
		exit(-1);
	}
	
	while(1)
	{
		struct dirent * direntp = NULL;
		direntp = readdir(dirp);	
		if(direntp == NULL && errno!=0)
		{
			perror("readdir fail");
			exit(-1);
		}
		

		if(direntp == NULL && errno == 0) break;

		//printf("inodeID=%lu, fname=%s\n", direntp->d_ino, direntp->d_name);
		printf("%s\n", direntp->d_name);
	}

	return 0;
}
