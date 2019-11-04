#include <stdio.h>
#include <unistd.h>

int main(void)
{
    long l = pathconf("file.t", _PC_NAME_MAX);
    printf("%ld\n", l);

    return 0;
}
