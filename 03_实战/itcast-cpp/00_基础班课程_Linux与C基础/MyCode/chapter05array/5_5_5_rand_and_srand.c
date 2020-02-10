/***********************************************************
 * @Description : 产生随机数
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 13:33
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <stdio.h>
#import <time.h>
#include <stdlib.h>

int main() {
    time_t tm = time(NULL); // 得到系统时间
    srand((unsigned int) tm); // 随机种子只要设置一次即可

    int r = rand();
    printf("r = %d\n", r);
    return 0;
}
/**
 */
