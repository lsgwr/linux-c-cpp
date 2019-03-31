#include <stdio.h>
#include <stdlib.h>

//extern char **environ;

int main(int argc, char **argv, char **environ)
{
	int i = 0;

	for(i=0; i<argc; i++)
	{
		printf("%s ", argv[i]);
	}
	printf("\n---------------------\n");

	
	for(i=0; NULL!=environ[i]; i++)
	{
		printf("%s\n", environ[i]);
	}
	printf("\n---------------------\n");

	
	return 0;
}

