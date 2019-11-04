#include <stdio.h>

extern int array[ ]; /* 导出全局变量array的声明 */
extern int sum();     /* 导出函数的声明 */
extern int get_max();
extern void print();

int main(void)
{
	int all, max;     /* 最大值 */

	all = sum();
	max = get_max(); /* 得到最大值 */
	print();           /* 打印数组元素 */
	printf("the sum : %d, the max : %d\n", all, max); /* 输出结果 */

	return 0;
}

