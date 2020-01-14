/***********************************************************
 * @Description : 按块写文件
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/15 7:36
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
    fp = fopen("./test.txt", "w");
    Stu s[3];
    int n = 3;
    for (int i = 0; i < 3; ++i) {
        sprintf(s[i].name, "stu%d%d%d", i, i, i);
        s[i].id = i + 1;
    }
    int ret = fwrite(s, sizeof(Stu), 3, fp);
    printf("ret = %d\n", ret);
    fclose(fp);
}

