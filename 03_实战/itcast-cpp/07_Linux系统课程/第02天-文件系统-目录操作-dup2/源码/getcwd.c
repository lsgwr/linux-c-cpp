#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void)
{
    char buf[64];
    printf("%s\n", getcwd(buf, 64));

    if (chdir("..") < 0) {
        perror("chdir error");
        exit(1);
    }

    printf("%s\n", getcwd(buf, 64));

    if (chdir("/home/itcast") < 0) {
        perror("chdir error");
        exit(1);
    }
    printf("%s\n", getcwd(buf, 64));
    int fd = open("haha.c", O_RDWR | O_CREAT | O_TRUNC, 0644);

    close(fd);

    return 0;
}
