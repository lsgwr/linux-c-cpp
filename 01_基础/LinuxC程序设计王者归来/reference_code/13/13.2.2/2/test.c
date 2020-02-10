#include <signal.h>
sig_atomic_t a;		/* 易失变量，使用volatile声明 */
void sigusr1_handler(int signo)
{
	a = 1;			/* 对易失变量进行赋值 */
}
int main(void)
{
	while(a == 0);	/* 一个表面上的死循环 */
	return 0;
}
