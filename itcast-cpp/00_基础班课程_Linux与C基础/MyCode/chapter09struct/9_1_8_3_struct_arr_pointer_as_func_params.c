/***********************************************************
 * @Description : 结构体数组指针作为函数参数
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/14 23：50
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>
#include <string.h>

struct stu {
    char name[50];
    int age;
};

// 函数参数为结构体普通变量，值传递，不会改变原值
void set_stu(struct stu *tmp, int n) {
    for (int i = 0; i < n; ++i) {
        sprintf(tmp->name, "name%d%d%d", i, i, i);
        tmp->age = 20 + i;
        tmp++; // 指针移动访问下一个元素
    }
}

int main() {
    struct stu s[3] = {0};
    int n = sizeof(s) / sizeof(s[0]); // 数组长度
    set_stu(s, n); // 值传递
    for (int i = 0; i < n; ++i) {
        printf("%s, %d\n", s[i].name, s[i].age);
    }
    return 0;
}
/**
name000, 20
name111, 21
name222, 22
 */
