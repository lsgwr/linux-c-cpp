#include <stdio.h>
#include <stdlib.h>
typedef struct node * Node;
Node head; /* 链表头 */
/* 链表结点结构
* val ：结点的值 
* next ：下一个结点的指针
*/
struct node{
	int val;
	Node next;
};
/* 插入结点函数 */
int insert(int val)
{
	Node p, q;
	p = head;
	if(p != NULL){ /* 寻找适当的插入位置 */
		while(p->next != NULL){
			p = p->next;	
		}
	}
	q = (Node)malloc(sizeof(struct node));	/* 创建一个新的结点 */
	if(q == NULL)
		return -1;
	q->next = NULL;							/* 对新结点进行赋值 */
	q->val = val;
	if(p == NULL){							/* 空链表 */
		head = q;
		return 1;	
	}
	p->next = q;							/* 新结点插入到链表中 */
	return 1;
}
void print()
{
	Node p = head;
	while(p != NULL){ /* 输出每个结点的值 */
		printf("%d\n", p->val);
		p = p->next;
	}
}
/* 遍历链表，释放每一个结点 */
void destroy()
{
	Node p = head;			/* 从链表的头开始 */
	while(p != NULL){		/* 当链表没有结束时 */
		Node q;
		q = p;
		p = p->next;		/* 释放链表的每一个结点 */
		free(q);	
	}	
	head = NULL;			/* 将头结点置空 */
}
int main(void)
{
	Node p;
	int i;
	int res = -1;
	printf("insert\n");
	for(i = 1; i< 8; i++)	/* 插入链表结点 */
		if(insert(i) == -1)
			goto err;		/* 出错则跳到err处进行资源释放 */
	print();				/* 遍历链表，打印链表结点 */
	res = 0;
err:
	destroy();				/* 销毁链表 */
	return res;				/* 程序结束状态 */
}
