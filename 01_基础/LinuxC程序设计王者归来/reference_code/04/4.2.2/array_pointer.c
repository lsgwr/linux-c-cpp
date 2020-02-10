#include <stdio.h>

int main(void)
{
	int a[5]={1,2,3,4,5};					/* 数组初始化 */
	int (*p)[5];							/* 数组指针 */
	int *ptr;

	p = &a;
	ptr = (int *)(p + 1);					/* 将数组的指针转换为整型的指针 */
	printf("the result is : %d", *(ptr-1));/* 输出该指针所指向的元素的值 */

	return 0;
}

