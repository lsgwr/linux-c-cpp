/***********************************************************
 * @Description : 
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/17 7:36
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>

struct People1 {
    char name[64];
    int age;
};

typedef struct People2 {
    char name[64];
    int age;
} people_t; // 给结构体类型取个别名

typedef unsigned int u32; // 给基本数据类型起个别名

int main(void) {
    struct People1 p1;
    people_t p2;
    u32 a;

    p1.age = 10;
    p2.age = 11;
    a = 10;
    return 0;
}