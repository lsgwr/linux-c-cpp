#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	char buf[64];
	char *p;
	system("ls -l");

	int ret = chdir(argv[1]);	//改变当前进程工作目录
	if(ret < 0){
		perror("chdir error");
		exit(1);
	}
	system("ls -l");

	chdir("..");			//改变当前进程当前工作目录

	system("ls -l");

	return 0;
}
