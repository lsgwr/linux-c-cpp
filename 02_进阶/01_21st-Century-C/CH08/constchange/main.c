#include <stdio.h>

void set_elm(int *a, int const *b) {
    a[0] = 3;
}

int main() {
    int a[3] = {};
    int const *b = a;
    set_elm(a, b); // 修改a也会影响b
    return 0;
}
