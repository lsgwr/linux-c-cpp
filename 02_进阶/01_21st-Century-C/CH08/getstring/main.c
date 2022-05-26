#include <stdio.h>
#include <stdlib.h>

void get_string(char const *in) {
    char *cmd;
    asiprintf(&cmd, "string %s", in);
    if (system(cmd)) {
        fprintf(stderr, "something went wrong running %s.\n", cmd);
    }
    free(cmd);
}

int main() {
    get_string("DIR");
    return 0;
}
