#include <stdio.h>
#include <stdlib.h>

typedef struct node * Node;					/* 自定义结点指针类型 */

static Node head;							/* 链表头 */

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
	
	if(p != NULL){ /* 链表非空 */
		while(p->next != NULL){
			p = p->next;	
		}	
	}	
	
	q = (Node)malloc(sizeof(struct node));	/* 创建一个新的结点 */
	if(q == NULL)
		return -1;
	q->next = NULL;							/* 对结点赋值 */
	q->val = val;
	
	if(p == NULL){ /* 空链表 */
		head = q;
		return 1;	
	}
	
	p->next = q; /* 结点链入链表 */

	return 1;
}

/* 遍历链表，打印每个结点的值 */
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
	Node p = head;

	while(p != NULL){ /* 遍历链表 */
		Node q;

		q = p;
		p = p->next; /* 到下一个结点 */
		free(q);      /* 释放该结点 */
	}	

	head = NULL;      /* 清空链表的头指针 */
}

