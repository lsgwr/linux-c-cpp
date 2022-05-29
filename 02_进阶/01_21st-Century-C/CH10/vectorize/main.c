#include <stdio.h>
#include <stdlib.h>

// 一次性对所有堆内存释放
#define Fn_Apply(type, fn, ...) { \
    void *stopper_for_apply = (int[]){0}; \
    type **list_for_apply = (type*[]){__VA_ARGS__, stopper_for_apply}; \
    for (int i = 0; list_for_apply[i] != stopper_for_apply; i++)       \
        fn(list_for_apply[i]);\
}

#define Free_all(...) Fn_Apply(void, free, __VA_ARGS__);

int main() {
    double *x = malloc(10);
    double *y = malloc(100);
    double *z = malloc(1000);
    Free_all(x, y, z);
    return 0;
}
