#include <stdio.h>
#include <stdarg.h>

/* 可变参数函数，其中第一个参数的类型是固定的，在定义的时候必须已经定义好 */
int print_args(int begin, ...)
{
	va_list ap;
	char *p;
	int n;

	va_start(ap, begin); 	/* 从可变参数的第一个参数开始遍历 */
	p = va_arg(ap, char *);	/* 得到第一个参数 */
	n = 0;

	while(p != NULL){	/* 可变参数以NULL结尾，在遇到NULL结束符之前输出所有的
						参数 */
		n++;			/* 累计参数的个数 */
		
		printf("arg %d : %s\n", n, p);	/* 输出每个参数 */
	
		p = va_arg(ap, char*); 			/* 得到下一个参数 */
	}
	
	va_end(ap);	/* 参数处理结束，做一些清理工作 */

	return n;	/* 返回参数的个数 */
}

int main(void)
{
	int n;
	
	n = print_args(-1, "hello", "world", NULL); /* 第一次调用，使用4个参数 */
	printf("first, without NULL : %d\n", n);
	
	n = print_args(-1, "China", "beijing", "Olympic", NULL);/* 第二次调用，
															  使用5个参数*/

	printf("second, without NULL : %d\n", n);
	return 0;
}

