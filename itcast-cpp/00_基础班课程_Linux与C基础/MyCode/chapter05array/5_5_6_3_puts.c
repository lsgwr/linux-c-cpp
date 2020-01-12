/***********************************************************
 * @Description : 字符串处理函数之puts(s)
 * 输出字符串s，在输出完成后自动输出一个换行符\n
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 13:53
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <stdio.h>

int main() {
    printf("hello world"); // 不会换行
    puts("hello"); // 会换行
    puts("world");
    return 0;
}
/**
hello worldhello
world
 */

