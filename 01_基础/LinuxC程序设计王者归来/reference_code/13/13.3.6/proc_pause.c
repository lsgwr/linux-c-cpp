#include <stdio.h>
#include <unistd.h>
int main(void)
{
	printf("start running\n");	/* 输出提示信息 */
	pause();					/* 进程暂停 */
	return 0;
}
