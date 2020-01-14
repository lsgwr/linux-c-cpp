/***********************************************************
 * @Description : 按行读文件
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/15 0:28
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *fp = NULL;

    // 以写方式打开文件
    fp = fopen("./test.txt", "r");
    char buf[100] = {0};
    while (!feof(fp)) {
        memset(buf, 0, sizeof(buf));
        char *p = fgets(buf, sizeof(buf), fp);
        if(p!=NULL){
            printf("buf = %s", buf);
        }
    }
    fclose(fp);
}
/**
buf = asds
buf = bsdfs
buf = cd
buf = dfsdgfsdfs
 */
