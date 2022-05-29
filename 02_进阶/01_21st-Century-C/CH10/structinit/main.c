#include <stdio.h>

typedef struct {
    int one;
    double two, three, four;
} n_s;

n_s justone = {10, .three = 8};

n_s threefour = {.two = 8, 3, 4};

int main() {
    printf("Hello, World!\n");
    return 0;
}
