#include "common.h"
/* 求序列中最大对象的函数，并且返回最大对象的位置
* array : 存储对象的数组，每个元素是一个指向对象的指针
* len : 存储对象的数组的元素个数
* func : 用于比较两个对象的回调函数
*/
void *max(void *array[], int len, cmp func)
{
	int i;
	void *tmp;

	tmp = array[0]; /* 初始时最大对象是数组中的第一个对象 */
	for(i = 1; i < len; i++) { /* 遍历数组，比较每个对象 */
		
		/* 比较两个对象，调用用户提供的比较函数。
		* 如果当前对象大于之前的最大对象，则替换掉最大对象 
		*/
		if((*func)(tmp, array [i]) == -1)
			tmp = array [i];
	}
	
	return tmp; /* 返回最大对象 */
}
