#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

char *my_getenv(const char *name)
{
	char *p = NULL;
	int i, len;

	for(i = 0; environ[i] != NULL; i++){
		p = strstr(environ[i], "=");
		len = p - environ[i];
		if(strncmp(name, environ[i], len) == 0){
			return p+1;
		}
	}

	return NULL;
}

int main(int argc, char *argv[])
{
	char *p = NULL;

	p = getenv(argv[1]);
	//p = my_getenv(argv[1]);

	if (p == NULL)
		printf("there is no match\n");
	else
		printf("%s\n", p);

	return 0;
}


