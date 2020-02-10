/***********************************************************
 * @Description : 内存分配malloc和释放free
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/1/13 23:55
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int count, *arr, n;
    printf("请输入要申请数组的个数:");
    scanf("%d", &n);

    arr = (int *) malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("申请空间失败！\n");
        return -1;
    }
    // 将申请到的空间清零
    memset(arr, 0, sizeof(int) * n);

    for (int i = 0; i < n; ++i) {
        arr[i] = i;
    }

    for (int i = 0; i < n; ++i) {
        printf("%d\t", arr[i]);
    }

    free(arr);
    return 0;
}
/**
请输入要申请数组的个数:20
20
0	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15	16	17	18	19
 */
