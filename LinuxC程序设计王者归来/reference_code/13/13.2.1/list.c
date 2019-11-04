#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>
typedef struct node * Node;	/* 自定义结点指针类型 */
Node head;					/* 链表头 */
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
	if(p != NULL){							/* 寻找适当的插入位置 */
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
/* 信号处理函数，向链表中插入一个新元素 */
void sigusr1_handler(int signo)
{
	if(insert(5) == -1){					/* 插入 */
		perror("fail to insert");
		exit(1);
	}
}
int main(void)
{
	int i = 0;
	while(i < 5){							/* 循环插入链表结点 */
		if(insert(i) == -1){				/* 出入失败则输出提示信息 */
			perror("fail to insert");
			exit(1);
		}
		i++;
	}
	return 0;
}
