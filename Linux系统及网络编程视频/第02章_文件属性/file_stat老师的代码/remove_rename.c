#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	//unlink("./file1.txt");
	//remove("./file2.txt");
	//remove("./kk");

	/* 移动 */
	rename("./file.txt", "../file.txt");
	rename("./kk", "../kk");


	
	
	

	return 0;
}
