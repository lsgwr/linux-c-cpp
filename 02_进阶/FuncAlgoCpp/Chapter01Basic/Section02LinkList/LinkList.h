/***********************************************************
 * @Description : 链表
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/11/24 23:15
 * @email       : liangshanguang2@gmail.com
***********************************************************/

#ifndef FUNCALGOCPP_LINKLIST_H
#define FUNCALGOCPP_LINKLIST_H

#include <iostream>

using namespace std;

template<typename T>
class ListNode;

template<typename T>
class LinkList {
private:
    ListNode<T> *head;

public:
    // 无参构造函数
    LinkList() {
        head = new ListNode<T>();
    }

    // 有参数构造函数
    LinkList(ListNode<T> *node) {
        head = node;
    }

    // 析构函数
    ~LinkList() {
        delete head;
    }

    bool insert(ListNode<T> *q, T newData); // 插入节点
    bool del(ListNode<T> *node); // 删除节点
    ListNode<T> *find(T val); // 获取指定值的节点并返回节点地址
    bool clear(); // 清空链表
    T getNodeData(ListNode<T> *node); // 获取节点数据
};

template<typename T>
class ListNode {
private:
    friend class LinkList<T>; // 将LinkList设为友元类，方便对node的成员数据和方法的访问

    T *next; // 指向下一个节点的指针
    T data; // 节点中的数据

public:
    ListNode() {
        next = NULL;
    }

    ListNode(T item, ListNode<T> *nextNode = NULL) {
        data = item;
        next = nextNode;
    }

    ~ListNode() {
        next = NULL;
    }

    // 获取节点内的数据
    T getData() {
        return data;
    }

    // 获取指针域
    ListNode *getNext() {
        return next;
    }
};

#endif //FUNCALGOCPP_LINKLIST_H
