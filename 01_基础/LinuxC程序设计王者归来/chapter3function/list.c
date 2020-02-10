// 链表操作
// Created by 梁山广 on 2018/1/13. P59
//

#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>

// 自定义指针类型
typedef struct node *Node;
static Node head;

struct node {
    // 节点的值
    int val;
    // 下一个节点的指针
    Node next;
};

/**
 * 节点插入函数
 */
int insert(int val) {
    Node p, q;
    p = head;
    if (p != NULL) {
        // 如果链表不为空
        while (p->next != NULL) {
            // 一直循环到待插入节点
            p = p->next;
        }
    }
    // 新建节点并分配存储空间
    q = (Node) malloc(sizeof(struct node));
    // 创建空间失败，返回-1表示失败，在主程序里得到-1直接退出
    if (q == NULL) {
        return -1;
    }
    q->next = NULL;
    q->val = val;
    if (p == NULL) {
        // 空链表的话
        head = q;
        return 1;
    }
    p->next = q;
    return 1;
}

/**
 * 遍历链表，输出每一个节点
 */
void print() {
    Node p = head;
    while (p != NULL) {
        // 输出每一个节点的值
        printf("%d\n", p->val);
        p = p->next;
    }
}

/**
 * 遍历链表，释放每一个节点
 */
void destroy() {
    Node p = head;
    while (p != NULL) {
        Node q;
        q = p;
        p = p->next;
        // 释放q，所以是一样的效果
        free(q);
    }
    // 最后释放头节点
    head = NULL;
}

int print_args(int begin, ...) {
    va_list ap;
    char *p;
    int n;
    // 从可变参数的第一个参数开始遍历
    va_start(ap, begin);
    // 得到第一个参数
    p = va_arg(ap, char*);
    n = 0;
    while (p != NULL) {
        // 累计参数个数
        n++;
        printf("arg %d : %s\n", n, p);
        // 获取下一个参数
        p = va_arg(ap, char*);
    }
    // 处理完毕，做一些清理工作
    va_end(ap);
    return n;
}








