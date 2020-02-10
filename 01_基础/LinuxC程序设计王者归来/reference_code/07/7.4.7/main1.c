#include <stdio.h>
#include "share_lib.h" /* 包含头文件，引用static_lib库中的函数 */

int main(void)
{
	int array[5] = {5, 4, 2, 3, 1};		/* 待排序数组 */
	int item;
	int pos;

	insert_sort(array, 5);					/* 直接插入排序 */
	
	printf("please input a number\n");
	scanf("%d", &item);					/* 输入一个数 */
	pos = binary_search(array, item, 5);	/* 二分查找该数 */
	
	if(pos == -1)
		printf("can’t find\n");				/* 没找到则输出说明信息 */
	else
		printf("the position is %d\n", pos + 1); /* 打印该数的位置 */

	return 0;
}
