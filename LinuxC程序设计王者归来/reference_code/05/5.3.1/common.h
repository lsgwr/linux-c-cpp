/* 头文件区 */
#include <stdio.h>
#include <stdlib.h>

/* 全局定义区，本程序没有用到宏，声明了一个结构体 */
typedef struct node * Node; /* 自定义结点指针类型 */

/* 链表结点结构
* val ：结点的值 
* next ：下一个结点的指针
*/
struct node{
	int val;
	Node next;
};

/* 全局变量声明区 */
extern Node head;

/* 函数接口声明区 */
extern int insert(int val);
extern int del(int val, Node * res);
extern void print();
extern void destroy();
