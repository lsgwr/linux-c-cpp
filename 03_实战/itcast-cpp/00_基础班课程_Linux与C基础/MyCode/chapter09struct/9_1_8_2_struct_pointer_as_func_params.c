/***********************************************************
 * @Description : 结构体指针作为函数参数
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/14 23：40
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>
#include <string.h>

struct stu {
    char name[50];
    int age;
};

// 函数参数为结构体普通变量，值传递，不会改变原值
void set_stu(struct stu *tmp) {
    strcpy(tmp->name, "mike");
    tmp->age = 18;
    printf("tmp->name = %s, tmp->age = %d\n", tmp->name, tmp->age);
}

int main() {
    struct stu s = {0};
    set_stu(&s); // 值传递
    printf("s.name = %s, s.age = %d\n", s.name, s.age);
    return 0;
}

