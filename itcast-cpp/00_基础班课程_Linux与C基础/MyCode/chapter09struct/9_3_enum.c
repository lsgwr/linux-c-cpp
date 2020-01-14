/***********************************************************
 * @Description : 枚举
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/14 23:58
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>

enum weekday {
    // 往后的元素自动递增1
    sun = 2, mon, tue, wed, thu, fri, sat
};

enum bool {
    false, true
};

int main(void) {
    enum weekday a, b, c;
    a = sun;
    b = mon;
    c = tue;
    printf("%d\t%d\t%d\n", a, b, c);

    enum bool flag;
    flag = true;
    if (flag == 1) {
        printf("flag为真！");
    }
    return 0;
}