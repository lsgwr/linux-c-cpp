#include <stdio.h>

int add(int a, int b)
{
	return a + b;			/* add函数内部不能引用mian函数中定义的局部变量 */
}

int main(void)
{
	int array[5];			/* 局部变量数组 */
	int i=0;

	while(i < 5){
		int res;			/* res定义在复合语句内部，因此res也是一个局部变量，
							在复合语句之外不能引用 */

		res = add(i, 1);	/* 对数组每个元素赋值 */
		array[i] = res;		/* 将结果保存在数组中 */
		i++;
	}
	
	for(i = 0; i < 5; i++)
		printf("array[%d] : %d\n", i + 1, array[i]); /* 输出每一个数组元素 */

	return 0;
}

