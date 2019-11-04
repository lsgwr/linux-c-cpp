#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int fd = open("readdir.c", O_RDONLY);
    if (fd == -1) {
        perror("open error");
        exit(1);
    }
    printf("...fd = %d\n", fd);
    int newFd = dup(fd);
    if (newFd == -1) {
        perror("dup error");
        exit(1);
    }
    printf("...newFd = %d\n", newFd);
    return 0;
}

