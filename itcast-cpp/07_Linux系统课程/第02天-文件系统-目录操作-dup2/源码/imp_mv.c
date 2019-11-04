#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	if(link(argv[1], argv[2]) == -1){
		perror("link error");
		exit(1);
	}

	if(unlink(argv[1]) == -1){
		perror("unlink error");
		exit(1);
	}

	return 0;
}
