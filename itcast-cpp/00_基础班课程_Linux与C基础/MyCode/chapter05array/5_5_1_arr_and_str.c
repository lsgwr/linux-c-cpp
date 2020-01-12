/***********************************************************
* @Description : 字符数组与字符串的区别
* @author      : 梁山广(Liang Shan Guang)
* @date        : 2020/1/12 12:32
* @email       : liangshanguang2@gmail.com
***********************************************************/
#include <stdio.h>

int main() {
    printf("不以反斜杠0作为结果会乱码：");
    char c1[] = {'c', ' ', 'p', 'r', 'o', 'g'};
    printf("c1 = %s\n", c1);

    printf("添加了反斜杠0不再乱码了：");
    char c2[] = {'c', ' ', 'p', 'r', 'o', 'g', '\0'};
    printf("c2 = %s\n", c2);

    printf("在字符串中间插入反斜杠0作为结束符，后面的字符不会输出：");
    char c3[] = {'c', ' ', 'p', 'r', 'o', 'g', '\0', 'h', 'e', 'l', 'l', 'o', '\0'};
    printf("c3 = %s\n", c3);
    return 0;
}
/**
 * 不以反斜杠0作为结果会乱码：c1 = c prog���
  * 添加了反斜杠0不再乱码了：c2 = c prog
 */
