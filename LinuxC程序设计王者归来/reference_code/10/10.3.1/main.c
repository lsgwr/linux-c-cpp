#include <stdio.h>
int main(int argc, char * argv[])
{
	int i;
	printf("count of arguments: %d\n", argc); /* 打印命令行参数的个数 */
	for(i = 0; i < argc; i++)
		printf("argv[%d]: %s\n", i, argv[i]); /* 逐个打印命令行参数 */
	return 0;
}
