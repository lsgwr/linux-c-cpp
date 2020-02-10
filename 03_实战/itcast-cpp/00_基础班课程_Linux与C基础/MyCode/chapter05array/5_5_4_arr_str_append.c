/***********************************************************
 * @Description : 字符串的追加
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 13:28
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <stdio.h>

int main() {
    char str1[] = "abcdef";
    char str2[] = "123456";
    char dst[100];

    int i = 0;
    // 0等效于\0
    while (str1[i] != 0) {
        dst[i] = str1[i];
        i++;
    }

    int j = 0;
    while (str2[j] != 0) {
        dst[i + j] = str2[j];
        j++;
    }
    dst[i + j] = 0; // 字符串结尾要设置结束符\0或0
    printf("拼接后的字符串：dts=%s\n", dst);
    return 0;
}
/**
拼接后的字符串：dts=abcdef123456
 */
