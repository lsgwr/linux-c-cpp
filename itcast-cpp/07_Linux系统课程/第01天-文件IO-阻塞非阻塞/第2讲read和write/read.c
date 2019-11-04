#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
    char buf[1024];
    // 每次读到的数据，用这个变量主要是怕最后一次读到的内容没有占满buf
    int ret = 0;
    int fd = open("./data.txt", O_RDWR);
    printf("fd = %d\n", fd);
    printf("error = %d\n", errno);
    while ((ret = read(fd, buf, sizeof(buf))) != 0)
    {
        write(STDOUT_FILENO, buf, ret);
    }
    close(fd);
    printf("close file with fd = %d\n", fd);
    return 0;
}
