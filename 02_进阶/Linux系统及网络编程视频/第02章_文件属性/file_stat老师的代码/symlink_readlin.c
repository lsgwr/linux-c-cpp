#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	symlink("./file.txt", "pfile");
	
	char sym_buf[30]  = {0};
	readlink("./pfile", sym_buf, sizeof(sym_buf));	
	printf("sym_buf = %s\n", sym_buf);
	
	

	return 0;
}
