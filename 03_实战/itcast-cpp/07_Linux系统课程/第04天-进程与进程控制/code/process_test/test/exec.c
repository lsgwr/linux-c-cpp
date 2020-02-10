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
        sleep(1);
        printf("I'am parent pid= %d, getppid = %d\n", getpid(), getppid());
    } else if (pid == 0) {
        char *argv[] = {"ls", "-l", "-a", "-F", NULL};

//        execl("/bin/ls", "ls", "-l", "-a", "-F", NULL);
//        execl("./test", "test",  NULL);
        execvp("ls", argv);
        perror("execlp");
        exit(1);
    }

    return 0;
}
