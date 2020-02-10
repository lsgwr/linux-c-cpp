#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	struct stat buf;

	int ret = stat("temp.txt", &buf);
	if(ret == -1){
		perror("stat error");
		exit(1);
	}

	printf("st_ino = %ld\n", buf.st_ino);
	printf("st_size = %ld\n", buf.st_size);
	printf("st_nlink = %d\n", buf.st_nlink);
	printf("st_uid = %d\n", buf.st_uid);
	printf("st_gid = %d\n", buf.st_gid);
	printf("st_mode = %x\n", buf.st_mode);

	return 0;
}
