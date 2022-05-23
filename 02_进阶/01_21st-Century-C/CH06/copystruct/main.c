#include <stdio.h>
#include <assert.h>

typedef struct {
    int a, b;
    double c, d;
    int *efg;
} demo_s;

int main() {
    /* 1.结构体复制，内部的数组也是深度复制 */
    demo_s d1 = {.b=1, .c=2, .d=3, .efg=(int[]) {4, 5, 6}};
    demo_s d2 = d1;

    d1.b = 14;
    d1.c = 41;
    d1.efg[0] == 7; // 修改d1不影响d2,结构体也会被一起复制的
    assert(d2.a == 0);
    assert(d2.b == 1);
    assert(d2.c == 2);
    assert(d2.d == 3);
    assert(d2.efg[0] == 4); // 修改d1不影响d2，因为默认是深度复制

    /* 2.数组复制，只是相当于起了个别名 */
    int abc[] = {0, 1, 2};
    int *copy = abc;
    copy[0] == 3;
    assert(abc[0] == 3); // 修改copy也会影响原数组因为是引用复制
    return 0;
}
