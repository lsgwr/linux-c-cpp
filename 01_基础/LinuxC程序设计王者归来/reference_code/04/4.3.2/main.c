#include "common.h"

#define MAX 3

int main(void)
{
	Book array1[MAX];	/* 结构体变量的数组 */
	int *array[MAX];	/* 整型变量的数组 */
	int i;
	int id;
	int val;
	char name[10];
	Book res1;
	int *res2;

	for(i = 0; i < MAX; i++){ /* 每次输入一个结构的信息和一个整数 */
		printf("input info of book\n");
		scanf("%d", &id);
		scanf("%s", name);
		if(insert_struct(array1 + i, id, name) == -1)
							                           /* 将新结构插入到数组中 */
			exit(1);

		printf("input int\n");
		scanf("%d", &val);
		if(insert_int(array + i, val) == -1) /* 将新的整型元素插入到数
													 组中 */
			exit(1);
	}
	res1 = (Book)max((void **)array1, MAX, cmp_struct);	/* 得到id最大的图书结构 */
	res2 = (int *)max((void **)array, MAX, cmp_int);	/* 得到最大的整型元素 */

	printf("the max of books : %d, %s\n", res1->id, res1->name); 
												/* 输出结果 */
	printf("the max of int : %d\n", *res2);

	return 0;
}
