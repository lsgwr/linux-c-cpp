#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(void)
{
    char *memp;

    int fd = open("/dev/zero", O_RDWR);

    memp = mmap(NULL, 40, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (memp == MAP_FAILED) {
        perror("mmap err");
        exit(1);
    }
    close(fd);

    pid_t pid = fork();
    if (pid > 0) {
        strcpy(memp, "aaa");
    } else if (pid == 0) {
        printf("--------%s\n", memp+1);
    }

    int ret = munmap(memp, 4);
    if (ret == -1) {
        perror("munmap err");
        exit(1);
    }

    return 0;
}
