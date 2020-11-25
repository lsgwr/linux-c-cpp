/***********************************************************
 * @Description : 
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/11/25 23:07
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#ifndef FUNCALGOCPP_DOUBLELIST_H
#define FUNCALGOCPP_DOUBLELIST_H

#include <iostream>

using namespace std;

template<typename T>
class DoubleList;

template<typename T>
class DoubleListNode {
private:
    T m_data; // 数据域
    DoubleListNode *m_pprior; // 指向前驱节点的指针域
    DoubleListNode *m_pnext; // 指向后继节点的指针域
    friend class DoubleList<T>; // 声明链表为友元类
    DoubleListNode() : m_pprior(NULL), m_pnext(NULL) {} // 无参构造函数，将指针初始化为NULL
    // 带参数构造函数初始化数据域和指针域
    DoubleListNode(const T item, DoubleListNode<T> *prior = NULL, DoubleListNode<T> *next = NULL) :
            m_data(item), m_pprior(prior), m_pnext(next) {}

    // 析构函数
    ~DoubleListNode() {
        m_pprior = NULL;
        m_pnext = NULL;
    }

public:
    T getData(); // 获取节点内的数据值
};

template<typename T>
T DoubleListNode<T>::getData() {
    return this->m_data;
}

template<typename T>
class DoubleList {
private:
    DoubleListNode<T> *head;

public:
    DoubleList(){
        head = new DoubleListNode<T>();
    }

    ~DoubleList() {
        clean();
        delete head;
    }

    void clean(); // 清空双向链表
    int getLen(); // 获取链表长度
    DoubleListNode<T> *findNode(int i = 0); // 寻找第i个节点
    DoubleListNode<T> *findData(T item); // 寻找具有给定值数据的节点
    bool insert(T item , int i); // 在第i个节点后插入新节点
    bool del(int i = 0); // 删除第i个节点
    T getData(int i = 0);// 删除第i个节点
};

template<typename T>
void DoubleList<T>::clean() {
    DoubleListNode<T> *pmove = head->m_pnext, *pdel;
    while (pmove!=NULL) { // 每次删除头结点后面的节点
        pdel = pmove;
        pmove = pdel->m_pnext;
        delete pdel;
    }
    head->m_pnext = NULL;
}

template<typename T>
int DoubleList<T>::getLen() {
    int cnt = 0;
    DoubleListNode<T> *pmove = head->m_pnext;
    // 遍历节点，计算节点数
    while (pmove!=NULL){
        pmove = pmove->m_pnext;
        cnt++;
    }
    return cnt;
}

template<typename T>
DoubleListNode<T> *DoubleList<T>::findNode(int i) {

    return nullptr;
}

template<typename T>
DoubleListNode<T> *DoubleList<T>::findData(T item) {
    return nullptr;
}

template<typename T>
bool DoubleList<T>::insert(T item, int i) {
    return false;
}

template<typename T>
bool DoubleList<T>::del(int i) {
    return false;
}

template<typename T>
T DoubleList<T>::getData(int i) {
    return nullptr;
}

#endif //FUNCALGOCPP_DOUBLELIST_H
