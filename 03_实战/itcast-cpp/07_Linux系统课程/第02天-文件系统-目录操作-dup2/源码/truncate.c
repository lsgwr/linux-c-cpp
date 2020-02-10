#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(void)
{
    int fd;

    fd = open("./file.t", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open error");
        exit(1);
    }

#if 0
    lseek(fd, 99, SEEK_SET);
    write(fd, "s", 1);

    close(fd);
#endif

    int ret = truncate("file.t", 200);
    if (ret < 0) {
        perror("open error");
        exit(1);
    }

    return 0;
}
