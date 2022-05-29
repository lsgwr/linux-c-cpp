#define _GNU_SOURCE

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>

int system_w_printf(char const *fmt, ...) __attribute__((format(printf, 1, 2)));

int system_w_printf(char const *fmt, ...) {
    char *cmd;
    va_list argp;
    va_start(argp, fmt);
    vasprintf(&cmd, fmt, argp);
    va_end(argp);
    int out = system(cmd);
    free(cmd);
    return out;
}

int main(int argc, char **argv) {
    assert(argc == 2);
    system_w_printf("DIR %s", argv[1]); // 列出指定目录下的内容
    return 0;
}
