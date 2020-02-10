#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

void sys_err(char *str)
{
    perror(str);
    exit(-1);
}

int main(int argc, char *argv[])
{
    int fd, i;
    char buf[4096];

    if (argc < 2) {
        printf("Enter like this: ./a.out fifoname\n");
        return -1;
    }
    /*
    int ret = access("myfifo", F_OK);
    if (ret != 0) {
        mkfifo("myfifo", 0664);
    }
    */

    fd = open(argv[1], O_WRONLY);
    if (fd < 0) 
        sys_err("open");

    i = 0;
    while (1) {
        sprintf(buf, "hello itcast %d\n", i++);
        write(fd, buf, strlen(buf));
        sleep(2);
    }
    close(fd);

    return 0;
}
