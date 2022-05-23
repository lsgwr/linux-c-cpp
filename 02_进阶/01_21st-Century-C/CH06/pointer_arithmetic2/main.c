#include <stdio.h>

typedef char *string;

int main() {
    string list[] = {"first", "second", "third", NULL};
    for (string *p = list; *p != NULL; p++) {
        printf("%s\n", *p);
    }
    return 0;
}
