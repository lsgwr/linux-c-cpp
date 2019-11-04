#include <stdio.h>
#include <setjmp.h>
jmp_buf env;			/* 保存当前的函数调用栈帧 */
/* 在函数内部实现一个全局跳转 */
void f(void)
{
	longjmp(env, 10);	/* 使用哪个保存栈帧的jmp_buf结构就跳到哪个位置 */
}
int main(void)
{
	int val;
	val = setjmp(env);	/* 设置一个跳转点 */
	if(val != 0)		/* 跳转回来后setjmp函数返回10. */
		printf("after long jump, the value is %d\n", val);
	else{				/* 在设置跳转点后，setjmp函数返回非0值 */
		printf("ready to jump\n");
	f();				/* 调用函数，在函数内部实现一个全局跳转 */
	}
	return 0;
}
