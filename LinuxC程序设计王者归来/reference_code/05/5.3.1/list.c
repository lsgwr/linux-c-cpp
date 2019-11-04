#include "common.h"

Node head; /* 链表头 */

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
	
	if(p == NULL){ /* 空链表 */
		head = q;
		return 1;	
	}
	
	p->next = q;				/* 新结点插入到链表中 */

	return 1;
}

/* 删除结点操作 */
int del(int val, Node * res)
{
	Node p, q;
	
	p = head;
	
	if(p == NULL)				/* 空链表 */
		return -1;

	if(p->val == val){			/* 第一个结点就是要删除的结点 */
		*res = p;
		head = p->next;			/* 删除这个结点 */

		return 1; 	
	}else if(p->next == NULL)	/* 只有一个结点，而且这个结点不是要删除的结点 */
		return -1;	
		
	q = p; 
	p = p->next; 				/* 两个指针并列前进 */
	while(p != NULL){
		if(p->val != val){		/* 找到要删除的结点 */
			q = p;
			p = p->next;	
		}else{
			q->next = p->next;	/* 删除结点 */
			p->next = NULL;
			*res = p;	

			return 1;			/* 成功删除结点，返回1 */
		}		
	}
	
	return -1;
}

/* 遍历链表，打印每个结点的值 */
void print()
{
	Node p = head;				/* 从链表的头开始 */

	while(p != NULL){			/* 当链表没有结束时 */
		printf("%d\n", p->val);	/* 输出每一个结点的值 */
		p = p->next;	
	}	
}

/* 遍历链表，释放每一个结点 */
void destroy()
{
	Node p = head;		/* 从链表的头开始 */

	while(p != NULL){	/* 当链表没有结束时 */
		Node q;

		q = p;
		p = p->next;	/* 释放链表的每一个结点 */
		free(q);	
	}	

	head = NULL;		/* 将头结点置空 */
}

