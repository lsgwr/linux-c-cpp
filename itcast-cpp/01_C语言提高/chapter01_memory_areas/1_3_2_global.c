/***********************************************************
 * @Description : 全局区
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/17 7:57
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>

char *getStr1(){
    char *p1 = "abcdefg1";
    return p1;
}

char *getStr2(){
    char *p2 = "abcdefg2";
    return p2;
}

int main(void){
    char *p1 = NULL;
    char *p2 = NULL;
    p1 = getStr1();
    p2 = getStr2();

    // 打印p1、p2指向的空间的数据
    printf("p1:%s, p2:%s \n", p1, p2);
    // 打印p1、p2指向的空间
    printf("p1:%p, p2:%p \n", p1, p2);
    return 0;
}
/*
p1:abcdefg1, p2:abcdefg2
p1:0x109718f7e, p2:0x109718f87
 */
