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

	//while(1);

	
	return 20;
}

