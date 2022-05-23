#include <stdio.h>

int main() {
    char *list[] = {"first", "second", "third", NULL};
    for (char **p = list; *p != NULL; p++) {
        printf("%s\n", p[0]);
    }
    return 0;
}
