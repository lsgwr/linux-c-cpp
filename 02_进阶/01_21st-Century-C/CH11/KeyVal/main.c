#include <stdio.h>
#include "dict.h"

int main() {
    int zero = 2;
    float one = 1.0f;
    char two[] = "two";
    dict *d = dict_new();
    dict_add(d, "an int", &zero);
    dict_add(d, "a float", &one);
    dict_add(d, "a string", &two);
    printf("The integer I recorded was: %i\n", *(int *) dict_find(d, "an int")); // 键的值是void *，所以打印的时候需要转化下
    printf("The string was: %s\n", (char *) dict_find(d, "s string")); // 字符串不用*取值，直接打印即可
    dict_free(d);
    return 0;
}
