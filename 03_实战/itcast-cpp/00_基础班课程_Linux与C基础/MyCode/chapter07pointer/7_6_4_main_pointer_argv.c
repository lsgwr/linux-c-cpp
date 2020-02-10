/***********************************************************
 * @Description : 指针数组作为main函数的形参
 *  指针数组，首先它是数组，其次它的每个元素都是指针，argv中每个元素都是指向字符串的指针，argv就相当于一个字符串数组
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 21:02
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("参数个数为：%d\n", argc);
    for (int i = 0; i < argc; ++i) {
        printf("%s\t", argv[i]);
    }
    return 0;
}
/**
参数个数为：4
/mnt/e/code/github/linux-c-cpp/itcast-cpp/00_基础班课程_Linux与C基础/MyCode/cmake-build-debug/7_6_4	para1	para2	para3
 */
