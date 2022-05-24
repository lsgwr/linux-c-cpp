/* 如何根据自己所选的命名模式生成大量的小型临时变量 */
#include <stdio.h>
#include <math.h>

#define Setup_list(name, ...) \
    double *name##_list = (double []){__VA_ARGS__, NAN}; \
    int name##_len = 0; \
    for (name##_len = 0; !isnan(name##_list[name##_len]);) {name##_len++;}

int main() {
    Setup_list(items, 1, 2, 4, 8);
    double sum = 0;
    for (double *ptr = items_list; !isnan(*ptr); ptr++) {
        sum += *ptr;
    }
    printf("total for items list: %g\n", sum);

    sum = 0;
    Setup_list(next_set, -1, 2.2, 4.8, 0.1);
    for (int i = 0; i < next_set_len; i++) {
        sum += next_set_list[i]; // next_set_list和next_set_len都被声明在全局变量中了
    }
    printf("total for next set list: %g, length is %d\n", sum, next_set_len);
    return 0;
}
