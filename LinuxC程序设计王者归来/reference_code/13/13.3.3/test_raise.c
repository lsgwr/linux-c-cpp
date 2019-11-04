#include <stdio.h>
#include <signal.h>
int main(void)
{
	printf("kill myself\n");				/* 输出提示信息 */
	raise(SIGKILL);							/* 该信号的处理方式是终结进程 */
	printf("should not be here, never\n");	/* 不可能执行到这里 */
	return 0;
}
