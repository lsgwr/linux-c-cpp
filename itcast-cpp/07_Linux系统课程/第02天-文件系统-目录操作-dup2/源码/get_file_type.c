#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	char *p;
	struct stat statbuf;

	int ret = lstat(argv[1], &statbuf);
	
	if(S_ISREG(statbuf.st_mode))
		p = "regular file";
	else if(S_ISDIR(statbuf.st_mode))
		p = "directory";
	else if(S_ISLNK(statbuf.st_mode))	//???
		p = "symbolic link";
	else if(S_ISCHR(statbuf.st_mode))
		p = "character device";
	else if(S_ISBLK(statbuf.st_mode))
		p = "block device";
	else if(S_ISFIFO(statbuf.st_mode))
		p = "named pipe";
	else if(S_ISSOCK(statbuf.st_mode))
		p = "socket";
	else
		p = "unknown";

	printf("\"%s\" is %s\n", argv[1], p);
	
	return 0;
}
