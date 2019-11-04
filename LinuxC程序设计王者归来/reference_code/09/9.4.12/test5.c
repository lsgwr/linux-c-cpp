#include <stdio.h>
int wib(int no1, int no2)
{
	int result, diff;
	diff = no1 - no2;				/* 求两个参数的差 */
	result = no1 / diff;			/* 计算参数1和差的商 */
	return result;
}
int main(int argc, char *argv[])
{
	int value, div, result, i, total;
	value = 10;					/* 对局部变量进行初始化 */
	div = 6;
	total = 0;
	for(i = 0; i < 10; i++)
	{
		result = wib(value, div);	/* 调用函数 */
		total += result;				/* 修改临时变量的值 */
		div++;
		value--;
	}
	printf("%d wibed by %d equals %d\n", value, div, total); /* 输出结果 */
	return 0;
}
