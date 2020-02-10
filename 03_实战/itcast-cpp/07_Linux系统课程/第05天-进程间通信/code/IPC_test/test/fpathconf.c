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
    pipe(fd);

    long len = fpathconf(fd[0], _PC_PIPE_BUF); 
    if (len == -1) {
        perror("fpahtconf error");
        exit(1);
    }
    printf("size of buf = %ld\n", len);

    return 0;
}
