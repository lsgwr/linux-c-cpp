#include <stdio.h>

/* 斐波那契数列计算 */
long long int fibonacci() {
    static long long int first = 0;
    static long long int second = 1;
    long long int out = first + second;
    first = second;
    second = out;
    return out;
}

int main() {
    for (int i = 0; i < 50; i++) {
        printf("%lli\n", fibonacci());
    }
    return 0;
}
