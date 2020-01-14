/***********************************************************
 * @Description : 按行写文件
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/15 0:28
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *fp = NULL;

    // 以写方式打开文件
    fp = fopen("./test.txt", "w");
    char *buf[] = {"123456\n", "bbbbbbbbbb\n", "cccccccccccc\n"};
    int n = 3;
    for (int i = 0; i < 3; ++i) {
        int len = fputs(buf[i], fp);
        printf("len = %d\n", len);
    }
    fclose(fp);
}

