#include <stdio.h>

typedef char *string;

int main() {
    string str = "thread";
    for (string *list = (string[]) {"yarn", str, "rope", NULL}; *list; list++) {
        printf("%s\n", *list);
    }
    return 0;
}
