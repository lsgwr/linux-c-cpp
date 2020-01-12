/***********************************************************
 * @Description : 字符串格式化函数sprintf(str, format)
 * 根据参数format指定的格式来格式化str，然后将结果输出到str指定的空间中
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/12 16:38
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include <stdio.h>
#include <string.h>

int main() {
    char dst[100] = {0};;
    int a = 10;
    char src[] = "hello world";
    printf("a = %d，src = %s\n", a, src);

    int len = sprintf(dst, "a = %d，src = %s\n", a, src);
    printf("%s\n", dst);
    printf("%d\n", len);
    return 0;
}
/**
返回值：111
返回值：0
 */

