#include <stdio.h>
#include <signal.h>
int main(void)
{
	sigset_t sig_set;
	sigemptyset(&sig_set);						/* 清空信号集 */
	sigaddset(&sig_set, SIGKILL);			/* 设置SIGKILL对应的位，注意
												   使用信号编码减1 */
	if((sigismember(&sig_set, SIGKILL)) == 1)	/* 测试该位是否已被设置 */
		printf("SIGKILL has been set\n");
	else
		printf("can’t set signal set\n");		/* 输出提示信息 */
	return 0;
}
