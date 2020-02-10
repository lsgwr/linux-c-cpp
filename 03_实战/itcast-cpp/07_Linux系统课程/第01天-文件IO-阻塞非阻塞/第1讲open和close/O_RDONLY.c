#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    // int open(const char *pathname, int flags);在fcntl.h中
    int fd = open("./data.txt", O_RDONLY);
    printf("fd = %d\n", fd);
    // 关闭文件函数，在Unistd.h中
    close(fd);
    return 0;
}

