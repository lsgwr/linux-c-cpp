#include <stdio.h>
#define MAX 10
int main(void)
{
	int array[MAX];
	int i;
	int max;
	for(i = 0; i < MAX; i ++)
		scanf("%d", &array[i]); 		/* 从标准输入读取数据 */
	max = array[0];
	for(i = 0; i < MAX; i++) 			/* 遍历数组，找到最大值 */
		if(max < array[i])
			max = array[i];
	printf("the result is %d\n", max); /* 将最大值输出到标准输出中 */
	return 0;
}
