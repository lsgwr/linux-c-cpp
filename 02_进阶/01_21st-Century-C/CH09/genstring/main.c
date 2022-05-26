#include <stdio.h>
#include <stdlib.h>

int main() {
    char *s1 = "Thread";
    char *s2;
    asprintf(&s2, "Floss");
    printf("%s\n", s1);
    printf("%s\n", s2);
    s2[0] = 'f';
    s1[0] = 't';
    free(s2);
    free(s1);
    return 0;
}
