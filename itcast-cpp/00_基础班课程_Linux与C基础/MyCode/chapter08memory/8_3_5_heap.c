/***********************************************************
 * @Description : 返回堆区地址
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/14 00:23
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>
#include <stdlib.h>

int *fun() {
    int *tmp = NULL;
    tmp = (int *) malloc(sizeof(int));
    *tmp = 100;
    return tmp; // 返回堆区地址，函数调用完毕，不释放
}

int main(void) {
    int *p = NULL;
    p = fun();
    printf("*p=%d\n", *p); // err,操作了空指针指向的内存
    // 堆区空间。使用完毕需要手动释放
    if (p != NULL) {
        free(p);
        p = NULL;
    }
    return 0;
}
/**
 * *p=100
 */
