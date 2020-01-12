/***********************************************************
 * @Description : 字符串处理函数之fputs(str,stream)
 * 将str所指定的字符串写入到stream指定的文件中，字符串结束符'\0'不写入文件
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 15:52
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <stdio.h>

int main() {
    printf("hello world"); // 不会换行
    puts("hello"); // 会换行
    puts("world");
    fputs("hello", stdout); // 不会换行
    fputs("world", stdout);
    return 0;
}
/**
hello worldhello
world
helloworld
 */

