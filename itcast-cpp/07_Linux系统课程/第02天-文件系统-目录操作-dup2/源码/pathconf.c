#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("%ld\n", pathconf("chdir", _PC_NAME_MAX));

    return 0;
}
