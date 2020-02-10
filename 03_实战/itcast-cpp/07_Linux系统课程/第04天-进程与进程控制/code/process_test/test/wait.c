#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid, wpid;
    int status;

    pid = fork();

    if (pid == 0) {
        sleep(300);
        printf("child, pid = %d\n", getpid());
        return 19;

    } else if (pid > 0) {
        printf("parent, pid = %d\n", getpid());
        wpid = wait(&status);
        printf("wpid ---- = %d\n", wpid);

        if (WIFEXITED(status)) {
            printf("exit with %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("killed by %d\n", WTERMSIG(status)); 
        }
    }

    return 0;
}
