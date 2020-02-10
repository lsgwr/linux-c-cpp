#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;

    pid = fork();

    if (pid == -1) {
        perror("fork error");
        exit(1);
    } else if (pid > 0) {
        printf("I'am parent pid= %d, getppid = %d\n", getpid(), getppid());

    } else if (pid == 0) {

        printf("I'am child pid= %d, ppid = %d\n", getpid(), getppid());
    }

    printf("------------finish---------------\n");

    return 0;
}
