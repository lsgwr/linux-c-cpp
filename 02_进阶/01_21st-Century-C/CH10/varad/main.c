#include <stdio.h>

#define forloop(i, loopmax, ...) for (int i = 0; i < loopmax; i++) \
{__VA_ARGS__}

int main() {
    int sum = 0;
    forloop(i, 10, sum += i; printf("sum to %i: %i\n", i, sum);)
    return 0;
}
