#include <stdio.h>
#include <unistd.h>
int f1()
{
	vfork( );		/* 在此函数中调用vfork函数 */
	return 0;	
}
int f2(int a, int b)
{
	return a + b;	/* 函数2，用来覆盖函数1的栈帧 */
}
int main()
{
	int c;
	f1( );			/* 调用vfork的函数 */
	c = f2(1,2);	/* 子进程可以运行到这里，父进程还可以吗？ */
	printf("%d\n", c);
	return 0;	
}
