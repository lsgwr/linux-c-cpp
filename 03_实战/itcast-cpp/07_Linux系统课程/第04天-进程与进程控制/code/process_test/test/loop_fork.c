#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    pid_t pid, wpid, tmpid;

    int i;
    for (i = 0; i < 5; i++) {
        pid = fork();
        if (pid  == 0) {
            break;
        }
        if (i == 2) {
            tmpid = pid;
        }
    }

//    sleep(i);

    if (5 == i) {
        printf("I'am parent pid= %d, getppid = %d\n", getpid(), getppid());
        while (i--) {
            wpid = waitpid(-1, NULL, 0);
            printf("wpid = %d\n", wpid);
        }

    } else {
        printf("I'm %dth child, pid = %d, ppid = %d\n", i+1, getpid(), getppid());
    }

    return 0;
}
