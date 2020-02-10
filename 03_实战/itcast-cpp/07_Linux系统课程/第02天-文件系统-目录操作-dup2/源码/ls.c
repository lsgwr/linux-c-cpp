#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	DIR *dp;
	struct dirent *sdp;
	int count = 0;

	dp = opendir(".");
	if(dp == NULL){
		perror("opendir error");
		exit(1);
	}

	while((sdp = readdir(dp)) != NULL){
		if(sdp->d_name[0] != '.')
			printf("%-10s%c", sdp->d_name, ++count % 5? '\t' : '\n');
	}

	closedir(dp);

	return 0;
}
