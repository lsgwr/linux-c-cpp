#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char *val;
	const char *name = "ABD";

	val = getenv(name);
	printf("1, %s = %s\n", name, val);

	setenv(name, "haha-day-and-night", 1);

	val = getenv(name);
	printf("2, %s = %s\n", name, val);

#if 0
	unsetenv("ABD");
	val = getenv(name);
	printf("3, %s = %s\n", name, val);
#else
	int ret = unsetenv("ABCEFJEW=");  //name=value:value
	printf("ret = %d\n", ret);

	val = getenv(name);
	printf("3, %s = %s\n", name, val);
#endif

	return 0;
}
