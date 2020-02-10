/***********************************************************
 * @Description : 结构体成员的基本使用
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/14 7:40
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>
#include <string.h>

struct stu{
    char name[50];
    int age;
};
int main(){
    struct stu s1;
    // 普通变量，通过点操作运算符操作结构体成员
    strcpy(s1.name, "abc");
    s1.age = 18;
    printf("s1.name = %s, s1.age = %d\n", s1.name, s1.age);

    // 如果是指针变量，通过->操作结构体成员
    strcpy((&s1)->name, "test");
    (&s1)->age = 22;
    printf("(&s1)->name = %s, (&s1)->age = %d\n", (&s1)->name, (&s1)->age);
    return 0;
}

