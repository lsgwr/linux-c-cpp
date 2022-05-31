#define _GNU_SOURCE //cause stdio.h to include vasprintf

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define System_w_printf(outval, ...) { \
    char *string_for_systemf;          \
    asprintf(&string_for_systemf, __VA_ARGS__); \
    outval = system(string_for_systemf);        \
    free(string_for_systemf);\
}

int main(int argc, char **argv) {
    assert(argc == 2);
    int out;
    System_w_printf(out, "DIR %s", argv[1]);
    return out;
}
