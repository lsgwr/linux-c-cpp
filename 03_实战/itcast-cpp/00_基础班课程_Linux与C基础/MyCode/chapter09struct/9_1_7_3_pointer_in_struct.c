/***********************************************************
 * @Description : 结构体套一级指针
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/14 23：30
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stu {
    char *name;
    int age;
};

int main() {
    struct stu *p = NULL;
    p = (struct stu *) malloc(sizeof(struct stu));

    // 如果是指针变量，通过->操作结构体成员
    p->name = malloc(strlen("test") + 1); // 给指针分配空间
    strcpy(p->name, "test");
    p->age = 22;

    printf("p->name = %s, p->age = %d\n", p->name, p->age);
    printf("(*p).name = %s, (*p).age = %d\n", (*p).name, (*p).age);

    if (p->name != NULL) { // 释放p之前要先释放p内部分配的变量
        free(p->name);
        p->name = NULL;
    }
    if (p != NULL) {
        free(p);
        p = NULL;
    }
    return 0;
}
/**
p->name = test, p->age = 22
(*p).name = test, (*p).age = 22
 */

