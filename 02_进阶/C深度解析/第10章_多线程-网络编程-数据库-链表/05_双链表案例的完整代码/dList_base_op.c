#include <stdio.h>
#include "dList_base_op.h"


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
DNode *Dou_CreateNode(void *data, int dataSize)
{
    /* malloc开辟节点空间 */
    DNode *p = (DNode *)malloc(sizeof(DNode));
    if(NULL == p) print_error("malloc");

    //让prev、next默认指向空
    p->prev = p->next = NULL;

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

/* 功能：将新节点插入到前后两个节点之前
 * 参数：
 *   prev：前一个节点的指针
 *   next：后一个节点的指针
 *   nodep：新节点的指针
 *
 * 返回值：无
 */
void Dou_insertNode(DNode *prev, DNode *next, DNode *nodep)
{
    //新节点与后一个节点相互发生指向
    nodep->next = next;
    next->prev = nodep;

    //新节点与前一个节点相互发生指向
    nodep->prev = prev;
    prev->next = nodep;
}

/* 功能：将新节点nodep，插入到p所指向节点的后面
*/
void Dou_InsertNodeAfter(DNode *p, DNode *nodep)
{
    Dou_insertNode(p, p->next, nodep);
}

/* 功能：将新节点nodep，插入到p所指向节点的前面
*/
void Dou_InsertNodeBefore(DNode *p, DNode *nodep)
{
    Dou_insertNode(p->prev, p, nodep);
}

/* 功能：插入到链表头部，也就是插到头节点的后面
 * hp：头节点指针
 * nodep：新节点的指针
 * 返回值：无
 */
void Dou_HeadInertNode(DNode *hp, DNode *nodep)
{
    Dou_InsertNodeAfter(hp, nodep); //插入到头节点的后面
}

/* 功能：插入链表尾部，也就是插到头节点的前面
 * hp：头节点指针
 * nodep：新节点的指针
 * 返回值：无
 */
void Dou_TailInertNode(DNode *hp, DNode *nodep)
{
    Dou_InsertNodeBefore(hp, nodep); //插入到头节点的前面
}

/* 功能：删除两个节点之前的节点
 * 参数：
 *    prev：前一个节点的指针
 *    next：后一个节点的指针
 * 返回值：无
*/
void Dou_Delete(DNode *prev, DNode *next)
{
    prev->next = next;
    next->prev = prev;
}

/* 功能：删除某个节点
 * 参数：
 *    p：要删除节点的指针
 * 返回值：无
*/
void Dou_DeleteNode(DNode *p)
{
    /* 删除节点 */
    Dou_Delete(p->prev, p->next);

    /* 释放节点空间 */
    if(NULL != p->data)
            free(p->data);//释放节点的数据空间
    p->data = NULL; //不要让遗留的随机值（节点指针），干扰下一次的空间使用
    p->prev = p->next = NULL;

    free(p); //释放节点空间
    p = NULL;
}
