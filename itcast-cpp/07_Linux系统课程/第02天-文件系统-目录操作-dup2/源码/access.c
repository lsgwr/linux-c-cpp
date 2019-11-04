#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int ret;
    if ((ret = access("abc", W_OK)) < 0) {
        printf("error ret = %d\n", ret);
        perror("abc");
        exit(1);
    }
    printf("ret = %d\n", ret);
    printf("abc is exist\n");

    return 0;
}
