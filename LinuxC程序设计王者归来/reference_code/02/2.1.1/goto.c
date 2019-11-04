#include <stdio.h>

int main(void)
{
	printf("the begin\n");	/* 输出提示信息 */
	goto end;				/* 使用goto语句实现跳转 */

	printf("hello world\n");
end:
	printf("the end\n");	/* end是一个标号，输出提示信息 */

	return 0;
}

