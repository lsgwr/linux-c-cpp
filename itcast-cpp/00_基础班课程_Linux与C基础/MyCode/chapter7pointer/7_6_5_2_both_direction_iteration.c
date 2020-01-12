/***********************************************************
 * @Description : 两头堵模型
 *  求非空字符串元素的个数
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 21:14
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>
#include <string.h>

int notEmptyCount(char *p) {
    int n = 0;
    if (p == NULL) {
        return -1;
    }
    int begin = 0;
    // 最后一个字符的下标记
    int end = strlen(p) - 1;

    // 从左边开始递增，如果当前字符为空，而且没有结束
    while (p[begin] == ' ' && p[begin] != 0) {
        begin++;
    }

    // 从右边开始递减，如果当前字符为空，而且没有结束
    while (p[end] == ' ' && p[end] != 0) {
        end--;
    }
    if (end == 0) {
        return -1;
    }

    return end - begin + 1;
}

int main(int argc, char *argv[]) {
    char *p = "     abcddsdsdfdgd     ";
    printf("非空字符串的元素个数为：%d\n", notEmptyCount(p));
    return 0;
}
/**
非空字符串的元素个数为：13
 */
