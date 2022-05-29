#include <stdio.h>

typedef char *string;

#define Foreach_string(it, ...) \
    for (string *it = (string[]){__VA_ARGS__, NULL}; *it; it++)

int main() {
    string str = "thread";
    Foreach_string(it, "yarn", str, "rope") {
        printf("%s\n", *it); // 用元素把中间变量取出来
    }
    return 0;
}
