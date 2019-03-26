#ifndef H_SLIST_BASE_OP_H
#define H_SLIST_BASE_OP_H
#include <stdlib.h> //exit函数需要这个头文件

#define print_error(str) \
do{\
  fprintf(stderr, "File %s, Line %d, Function %s error\n", __FILE__, __LINE__, __func__);\
  perror(str);\
  exit(-1);\
}while(0);

typedef struct SignalNode  //单链表结构
{
    void *data;
    struct SignalNode *prev; //指向上一个元素
    struct SignalNode *next; //指向下一个元素
}DNode;


extern DNode *Dou_CreateNode(void *data, int dataSize);
extern void Dou_insertNode(DNode *prev, DNode *next, DNode *nodep);
extern void Dou_InsertNodeAfter(DNode *p, DNode *nodep);
extern void Dou_InsertNodeBefore(DNode *p, DNode *nodep);
extern void Dou_Delete(DNode *prev, DNode *next);
extern void Dou_DeleteNode(DNode *prevNodep);
extern void Dou_HeadInertNode(DNode *hp, DNode *node);
extern void Dou_TailInertNode(DNode *hp, DNode *node);

#endif
