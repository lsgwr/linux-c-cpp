#include <stdio.h>
#define DEBUG 1								/* 调试开关 */
#ifdef DEBUG
#define PRINT(str) printf(str);			/* 输出一个参数的printf函													数 */
#define PRINT!(str, arg); printf(str, arg); /* 输出两个参数的printf函数 												*/
#else
#define PRINT(str) ;				/* 定义该宏为空语句 */
#define PRINT!(str, arg); ;
#endif
int main(void)
{
	int array[5] = {1,2,4,3, 0};
	int i;
	PRINT("before sort\n");
	bubble_sort(array, 5);			/* 调用冒泡排序函数 */
	PRINT("after sort\n");
	for(i = 0; i < 5; i++)
		PRINT("%d\n", array[i]);	/* 输出每一个数组元素 */
	return 0;
}
