#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(void)
{
    int ret = mkdir("testdir111", 0755);
    printf("ok...\n");

    return 0;
}

