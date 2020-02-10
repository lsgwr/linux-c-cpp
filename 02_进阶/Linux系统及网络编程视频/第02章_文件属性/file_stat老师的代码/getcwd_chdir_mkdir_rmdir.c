#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	//char *getcwd(char *buf, size_t size);
	
#if 0
	char buf[100] = {0};
	char *p = getcwd(buf, 100);

	printf("buf = %s\n", buf);
	
	//printf("p = %p\n", p);
	//printf("buf = %p\n", buf);
	
	//chdir("../");
	chdir("/home");
	
	getcwd(buf, 100);
	printf("buf = %s\n", buf);

#endif
	
	int ret =rmdir("./kk");
	if(-1 == ret)
	{
		perror("rmdir fail");
		exit(-1);
	}



	return 0;
}
