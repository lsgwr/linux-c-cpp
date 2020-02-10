/***********************************************************
 * @Description : 项目中常用的字符串应用模型
 *  strstr中的while和do-while模型:使用strstr标准库函数找出一个字符串
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 21:14
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *p = "11abcd11122abcd333abcd3322abcd3333322qqq";
    int n = 0; // 匹配到目标字符串的次数
    while ((p = strstr(p, "abcd")) != NULL) { // 只要还能继续往后找就继续循环下去
        // 能进来，至少匹配到一次
        p += strlen("abcd");
        n++; // 匹配数累计
        if (*p == 0) { // 如果到了结束符
            break;
        }
    }
    printf("累计匹配到的次数：%d\n", n);
    return 0;
}
/**
累计匹配到的次数：4
 */
