#include <stdio.h>
int main(void)
{
	printf("int : %d\n", sizeof(int));				      /* 整型的大小 */
	printf("short : %d\n", sizeof(short));			      /* 短整型的大小 */
	printf("char : %d\n", sizeof(char));			      /* 字符型的大小 */
	printf("unsigned int : %d\n", sizeof(unsigned));    /* 无符号整型的大小*/
	printf("long : %d\n", sizeof(long));			      /* 长整型的大小 */

	/* 输出真正的长整型，在32位体系结构中为64位 */
	printf("long long: %d\n", sizeof(long long));
	printf("float : %d\n", sizeof(float));			     /* 浮点型的大小 */
	printf("double : %d\n", sizeof(double));		     /* 双精度型的大小 */
	printf("long double : %d\n", sizeof(long double)); /* 长双精度型的大
														 小 */
	return 0;
}

