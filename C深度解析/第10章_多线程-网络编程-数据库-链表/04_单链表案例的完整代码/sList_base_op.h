#ifndef H_SLIST_BASE_OP_H
#define H_SLIST_BASE_OP_H
#include <stdlib.h> //exit函数需要这个头文件

#define print_error(str) \
do{\
    fprintf(stderr, "File %s, Line %d, Function %s error\n", __FILE__, __LINE__, str);\
    perror("error Reason");\
    exit(-1);\
}while(0); 

typedef struct SignalNode  //单链表结构
{
    void *data;
    struct SignalNode *next; //指向下一个元素
}SNode;


extern SNode *Sig_CreateNode(void *data, int dataSize);
extern void Sig_InsertNode(SNode *p, SNode *node);
extern void Sig_DeleteNode(SNode *prevNodep);
extern void Sig_HeadInertNode(SNode *hp, SNode *node);
extern void Sig_TailInertNode(SNode *hp, SNode *node);

#endif
