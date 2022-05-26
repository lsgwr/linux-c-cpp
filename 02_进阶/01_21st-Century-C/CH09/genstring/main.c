#include <stdio.h>

int main() {
    char *s1 = "Thread";
    char *s2;
    asprintf(&s2, "Floss");
    printf("%s\n", s1);
    printf("%s\n", s2);
    return 0;
}
