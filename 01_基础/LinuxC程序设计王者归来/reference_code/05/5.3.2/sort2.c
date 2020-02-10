#include <stdio.h>
int main(void)
{
	int array[5] = {1,2,4,3, 0};	/* 初始化数组 */
	int i;
	/* printf("before sort\n"); */
	bubble_sort(array, 5);			/* 调用冒泡排序函数 */
	/* printf("after sort\n"); */
	 /* for(i = 0; i < 5; i++)
		printf("%d\n", array[i]); 输出元素同样注释掉*/
	return 0;
}
