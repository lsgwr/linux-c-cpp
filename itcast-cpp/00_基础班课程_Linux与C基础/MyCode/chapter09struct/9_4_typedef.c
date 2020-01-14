/***********************************************************
 * @Description : typedef 为数据类型定义一个新的名字
 *
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/15 0:04
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>

typedef int INT;
typedef char BYTE;
typedef BYTE T_BYTE;
typedef unsigned char UBYTE;

typedef struct type {
    UBYTE a;
    INT b;
    T_BYTE c;
} TYPE, *PTYPE;

int main(void) {
    TYPE t;
    t.a = 254;
    t.b = 10;
    t.c = 'c';

    PTYPE p = &t;
    printf("%u, %d, %c\n", p->a, p->b, p->c);
}
/**
 * 254, 10, c
 */
