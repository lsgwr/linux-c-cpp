#include <stdio.h>

int main() {
    int evens[5] = {0, 2, 4, 6, 8};
    printf("evens数组的第1个元素为：%i\n", *evens);
    int *positive_evens = &evens[1];
    printf("新的指针数组的第1个元素：%d\n", positive_evens[0]);
    return 0;
}
/**
 * evens数组的第1个元素为：0
 * 新的指针数组的第1个元素：2
 */
