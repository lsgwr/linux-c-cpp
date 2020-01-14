/***********************************************************
 * @Description : 栈区的结构体变量
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/14 23：26
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stu {
    char name[50];
    int age;
};

int main() {
    struct stu *p = NULL;
    p = (struct stu *) malloc(sizeof(struct stu));

    // 如果是指针变量，通过->操作结构体成员
    strcpy(p->name, "test");
    p->age = 22;

    printf("p->name = %s, p->age = %d\n", p->name, p->age);
    printf("(*p).name = %s, (*p).age = %d\n", (*p).name, (*p).age);

    free(p);
    p = NULL;
    return 0;
}
/**
 p->name = test, p->age = 22
(*p).name = test, (*p).age = 22
 */

