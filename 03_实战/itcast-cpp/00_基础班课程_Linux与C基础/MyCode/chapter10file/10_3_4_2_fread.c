/***********************************************************
 * @Description : 按块读文件
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/15 7:41
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>
#include <string.h>

typedef struct stu {
    char name[50];
    int id;
} Stu;

int main(void) {
    FILE *fp = NULL;

    // 以写方式打开文件
    fp = fopen("./test.txt", "r");
    int n = 3;
    Stu s[3];
    int ret = fread(s, sizeof(Stu), 3, fp);
    printf("ret = %d\n", ret);
    for (int i = 0; i < 3; ++i) {
        printf("s = %s, %d\n", s[i].name, s[i].id);
    }
    fclose(fp);
}
/*
ret = 3
s = stu000, 1
s = stu111, 2
s = stu222, 3
 */
