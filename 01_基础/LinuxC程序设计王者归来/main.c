#include <stdio.h>
#include <stdlib.h>
#include "chapter3function/list.h"
#include "chapter11process/myprocess.h"

/**
 * 测试链表的插入、删除等基本操作
 */
void testList() {
    int i;
    for (int i = 0; i < 5; ++i) {
        if (insert(i) == -1) {
            // 如果插入失败
            exit(1);
        }
    }
    // 打印所有的链表节点
    print();
    // 释放链表
    destroy();
}

/**
 * 测试动态参数
 */
void testArgs() {
    int n = print_args(-1, "hello", "world", "test", NULL);
    printf("不统计NULL的参数的个数：%d\n", n);
}

/**
 * 第11章：进程控制
 */
void testProcess() {
    createProcess();
}

int main() {
    //testArgs();
    testProcess();
    return 0;
}

