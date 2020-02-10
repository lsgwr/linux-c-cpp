#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(void)
{
	int i;

	for(i = 0; i < 5; i++)	/* 使用insert函数插入5个结点 */
		if(insert(i) == -1)
			exit(1);

	print();				/* 输出链表的所有结点 */

	destroy();				/* 销毁链表 */

	return 0;
}

