#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char buf[1024];

	if(chdir("..") == -1){      //shell  cd
		perror("chdir error");
		exit(1);
	};

	if(getcwd(buf, 1024) == NULL){  //shell pwd
		perror("error");
		exit(1);
	}

	printf("wd = %s\n", buf);

	return 0;
}
