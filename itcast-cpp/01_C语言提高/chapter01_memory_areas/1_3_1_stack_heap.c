/***********************************************************
 * @Description : 栈区和堆区
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/17 7:49
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 堆：malloc、new、free、delete
char *getMem1(int num) {
    char *p1 = NULL;
    p1 = (char *) malloc(sizeof(char) * num);
    if (p1 == NULL) {
        return NULL;
    }
    return p1;
}

// 栈区：局部变量
char *getMem2(){
    char buf[64]; // 局部变量，栈区存放
    strcpy(buf, "123456789");
    return buf;
}

int main(void){
    char *tmp = NULL;
    tmp = getMem1(10);
    if (tmp == NULL){
        return -1;
    }
    strcpy(tmp, "2222111"); // 向堆中的tmp指向的内存空间copy数据
    printf("%s\n", tmp);
    tmp = getMem2();
    printf("%s\n", tmp); // 打印为空，因为栈中的变量出了函数就被释放了
    return 0;
}