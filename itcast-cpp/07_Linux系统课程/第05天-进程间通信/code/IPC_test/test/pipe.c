#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

int main(void)
{
    int fd[2];
    int ret;
    pid_t pid;
    char *str = "hello pipe\n";
    char buf[1024];
    ret = pipe(fd);
    if (ret == -1)
        sys_err("pipe error");

    pid = fork();
    if (pid == -1)
        sys_err("fork error");

    else if (pid > 0) {
        close(fd[0]);
        sleep(2);
        write(fd[1], str, strlen(str));
        wait(NULL);
        close(fd[1]);
    } else if (pid == 0) {
        close(fd[1]);
        ret = read(fd[0], buf, sizeof(buf));
        write(STDOUT_FILENO, buf, ret);
        close(fd[0]);
    }
    
    return 0;
}
