#include <stdio.h>

#define MAX 5
int array[MAX] = {2,7,6,4,8, };

/* 计算数组中所有元素的和 */
int sum()
{
	int i;
	int n; 						/* 临时变量 */

	n = 0;
	for(i = 0; i < MAX; i++)	/* 遍历数组，累加每个数组元素，计算数组中所有元素
								   的和 */
		n += array[i];

	return n;
}

/* 得到数组中最大的元素 */
int get_max()
{
	int max;
	int i;
	
	i = 0;
	max = array[i];
	for(i = 0; i < MAX; i ++) /* 遍历数组，比较每个元素，得到数组中最大的元素 */
		if(array[i] > max)
			max = array[i];    /* 找到最大的值 */

	return max;
}

/* 输出数组中每个元素的值 */
void print()
{
	int i;                        /* 临时变量，作为循环因子 */

	for(i = 0; i < MAX; i++)  /* 遍历数组，输出数组中每个元素的值 */
		printf("array[%d] : %d\n", i + 1, array[i]);
}

