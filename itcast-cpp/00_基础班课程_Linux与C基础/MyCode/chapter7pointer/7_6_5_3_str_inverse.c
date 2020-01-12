/***********************************************************
 * @Description : 字符串反转
 *  求非空字符串元素的个数
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 21:14
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>
#include <string.h>

void inverse(char *p) {
    if (p == NULL) {
        return;
    }
    int begin = 0;
    // 最后一个字符的下标记
    int end = strlen(p) - 1;

    while (begin < end) {
        // 交换元素
        char tmp = p[begin];
        p[begin] = p[end];
        p[end] = tmp;
        begin++;
        end--;
    }
}

int main(int argc, char *argv[]) {
    // 如果是char *p = "abcdefg"; 则字符串为常量，内容不能修改
    char p[] = "abcdefg";
    inverse(p);
    printf("反转后为：%s\n", p);
    return 0;
}
/**
反转后为：gfedcba
 */
