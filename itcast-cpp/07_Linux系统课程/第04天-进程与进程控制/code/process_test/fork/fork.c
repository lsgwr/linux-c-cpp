#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    pid_t pid;

    pid = fork();
    if (pid == -1 ) {
        perror("fork");
        exit(1);
    } else if (pid > 0) {

        while (1) {
            printf("I'm parent pid = %d, parentID = %d\n", getpid(), getppid());
            sleep(1);
        }
    } else if (pid == 0) {
        while (1) {
            printf("child  pid = %d, parentID=%d\n", getpid(), getppid());
            sleep(1);
        }
    }

    return 0;
}
