#include "common.h"

int main(void)
{
	Node p;
	int i;
	
	printf("insert\n");
	for(i = 1; i< 8; i++) 	/* 插入链表结点 */
		insert(i);
	print();				/* 遍历链表，打印链表结点 */
	
	printf("destroy\n");
	destroy(); 				/* 销毁链表 */
		 
	return 0;	
}
