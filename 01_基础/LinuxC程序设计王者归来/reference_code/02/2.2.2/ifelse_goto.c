#include <stdio.h>

int main(void)
{
	int a, b;						/* 两个临时变量a和b */
	int t;

	scanf("%d%d", &a, &b);			/* 输入变量a和b的值 */

	t = a > b;						/* t为临时值，保存条件表达式运算后的结果 */
	if(t == 1)
		goto true;
	printf("a is lower than b\n");	/* 执行else的语句 */

	goto done;						/* 跳转到程序结束处 */
true:
	printf("a is higher than b\n");/* 执行条件表达式满足时的语句 */

done:								/* 结束执行的标号 */
	return 0;
}

