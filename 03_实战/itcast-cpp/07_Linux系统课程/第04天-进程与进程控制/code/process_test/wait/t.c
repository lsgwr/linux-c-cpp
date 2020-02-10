#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("-----1-----\n");
    pid_t pid = fork();

    printf("----2----\n");
    if (pid > 0) {
        printf("-----parent=----\n");
    } else {
        printf("-----child\n");
    }

    printf("----3----\n");

    return 0;
}
