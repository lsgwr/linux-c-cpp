/***********************************************************
 * @Description : 按照字符读文件
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/15 0:28
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *fp = NULL;
    char ch;
    // 以写方式打开文件
    fp = fopen("./test.txt", "r");
    while (!feof(fp)) {
        ch = fgetc(fp);
        printf("%c", ch);
    }
    // 关闭文件
    fclose(fp);
}

