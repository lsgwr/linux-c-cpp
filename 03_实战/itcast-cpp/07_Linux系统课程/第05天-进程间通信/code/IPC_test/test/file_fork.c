#include <unistd.h>
#include <fcntl.h>
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
    int fd = open("testFile", O_RDWR | O_TRUNC | O_CREAT, 0664);
    if (fd == -1)
        sys_err("open err");
    int ret;
    char buf[1024];

    pid_t pid = fork();
    if (pid == -1)
        sys_err("fork err");

    if (pid > 0) {
        write(fd, "hello\n", strlen("hello\n"));
        printf("----write finish ----\n");
        wait(NULL);
    } else if (pid == 0) {
        sleep(1);
        lseek(fd, 0, SEEK_SET);
        ret = read(fd, buf, sizeof(buf));
        write(STDOUT_FILENO, buf, ret);
    }
    
    return 0;
}
