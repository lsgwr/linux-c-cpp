#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char * argv[])
{
    struct stat sbuf;

    int ret = stat(argv[1], &sbuf);         //穿透符号链接
    if (ret < 0) {
        perror("stat");
        exit(1);
    }

    printf("inode = %d\n", (int)sbuf.st_ino);
    printf("size = %d\n", (int)sbuf.st_size);

    if (S_ISREG(sbuf.st_mode)) {
        printf("It's a regular file\n");
    } else if (S_ISDIR(sbuf.st_mode)) {
        printf("It's a directory\n");
    } else if (S_ISFIFO(sbuf.st_mode)) {
        printf("It's a fifo\n");
    } else if (S_ISLNK(sbuf.st_mode)) {
        printf("It's a symbolic link\n");
    }

    return 0;
}
