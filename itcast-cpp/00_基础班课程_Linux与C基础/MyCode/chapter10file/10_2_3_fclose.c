/***********************************************************
 * @Description : 文件关闭
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/15 0:28
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>

int main(void) {
    FILE *fp = NULL;

    // 以写方式打开文件
    fp = fopen("./test.txt", "w");
    if (fp == NULL) {
        perror("open"); // perror()是标准出错打印函数，能打印调用库函数出错的原因
        return -1;
    }
    fclose(fp);
}

