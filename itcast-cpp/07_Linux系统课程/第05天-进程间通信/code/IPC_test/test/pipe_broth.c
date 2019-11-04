#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int fd[2];
    int i;
    pid_t pid, wpid;
    pipe(fd);

    for  (i = 0; i < 2; i++) {
        pid = fork();
        if (pid == 0)
            break;
    }
        
    if (2 == i) {
        close(fd[0]);
        close(fd[1]);
        wpid = wait(NULL);
        printf("wait child 1 success pid = %d\n", wpid);
        wpid = wait(NULL);
        printf("wait child 2 success pid = %d\n", wpid);

    } else if (i == 0) {  //兄
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execlp("ls", "ls", NULL);
    } else if (i == 1) {   //弟
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        execlp("wc", "wc", "-l", NULL);
    }

    return 0;
}
