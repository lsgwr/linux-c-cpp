// 学习错误处理
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
    int fd = open("./test.txt", O_RDWR | O_TRUNC);
    printf("fd = %d\n", fd);
    printf("errno = %d\n", errno);
    close(fd);
    printf("close file with fd = %d\n", fd);
    return 0;
}

