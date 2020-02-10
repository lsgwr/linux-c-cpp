#include <stdio.h>
#include <string.h>
#include "sList_base_op.h"


/* 功能：创建节点
 * 参数：
 *      data：指向空间中，存放了要被写入节点的数据
 *          如果data为NULL，就表示没有数据要存入节点，
 *          此时只是一没有数据的空节点
 *
 *      dataSize：数据空间的大小
 *
 * 返回值：返回新节点的指针（结构变量首字节地址）
 */
SNode *Sig_CreateNode(void *data, int dataSize)
{
    /* malloc开辟节点空间 */
    SNode *p = (SNode *)malloc(sizeof(SNode));
    if(NULL == p) print_error("malloc");

    //让next默认指向空
    p->next = NULL;

    /* malloc开辟节点中的数据空间，然后存入数据
     * 有数据才开辟，没有数据就不用开辟了
    */
    if(NULL != data)
    {
        p->data = malloc(dataSize);
        if(NULL == p) print_error("malloc");

        //前面的课程就说过，结构体变量之间是可以整体复值的
        memcpy(p->data, data, dataSize);
    }

    return p;
}


/* 功能：通用插入函数
 * 参数：
 *      prevNodep：放的是要插入位置前一个节点的指针
 *      node：放的是要插入节点的指针
 * 返回值：无
*/
void Sig_InsertNode(SNode *p, SNode *node)
{
    node->next = p->next;
    p->next = node;
}

/* 功能：在链表头部不插入，也就是头节点后的位置插入
 * hp：链表头指针
 * node：要插入节点的指针
 * 返回值：无
 */
void Sig_HeadInertNode(SNode *hp, SNode *node)
{
    Sig_InsertNode(hp, node);
}

/* 功能：在链表尾部插入，也就是链表最后一个节点的后面插入
 * hp：链表头指针
 * node：要插入节点的指针
 * 返回值：无
 */
void Sig_TailInertNode(SNode *hp, SNode *node)
{
    SNode *p = hp;
    while(1)
    {
        if(p->next == NULL)
        {
            Sig_InsertNode(p, node);
            break;
        }
        p = p->next;
    }
}

/* 功能：删除节点
 * 参数：
 *      prevNodep：放的是要删除节点的前一个节点的指针
 * 返回值：无
*/
void Sig_DeleteNode(SNode *p)
{
    /* 记住要被删除的节点的指针 */
    SNode *temp = p->next;

    /* 删除节点 */
    p->next = p->next->next;

    /* 释放节点空间 */
    if(temp != NULL) free(temp->data);//释放节点的数据空间
    temp->data = NULL;//不要让遗留的随机值（节点指针），干扰下一次的空间使用

    free(temp); //释放节点空间
    temp = NULL;
}
