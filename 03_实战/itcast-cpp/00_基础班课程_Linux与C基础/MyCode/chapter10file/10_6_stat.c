/***********************************************************
 * @Description : 文件状态
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/15 7:52
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void){
    char path[] = "./test.txt";
    struct stat st = {0};
    stat(path, &st);
    int size = st.st_size; // 得到结构体中的成员变量
    printf("%d\n", size);
    return 0;
}
