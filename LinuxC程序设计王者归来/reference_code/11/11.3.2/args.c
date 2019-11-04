#include <stdio.h>
/* main函数需要参数 */
int main(int argc, char * argv[])
{
	int i;						/* 循环因子 */
	for(i = 0; i < argc; i++)	/* 输出每个命令行参数，该参数是字符串的形式的 */
		printf("argv[%d] : %s\n", i, argv[i]);
	return 0;
}
