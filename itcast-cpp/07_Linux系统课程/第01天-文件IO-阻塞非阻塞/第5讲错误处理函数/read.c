#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char buf[1024];
    // 每次读到的数据，用这个变量主要是怕最后一次读到的内容没有占满buf
    int ret = 0;
    int fd = open("./data.txt", O_RDWR);
    if (fd == -1)
    {
        printf("open error1! errno = %d\n", errno);
        // 1.错误打印1：自动会把传入的字符串和实际的错误拼接起来。perror在stdlib.h中
        perror("open error2");
        // 2.错误打印2：传入errno返回出错的字符串，在string.h中
        printf("open error3: %s", strerror(errno));
        exit(1);
    }

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
