// 复制文件，范例./cp data.txt data2.txt
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
    char buf[1024];
    // 每次读到的数据，用这个变量主要是怕最后一次读到的内容没有占满buf
    int ret = 0;
    int fd_read = open(argv[1], O_RDONLY);
    // 文件存在就覆盖复制
    int fd_write = open(argv[2], O_RDWR | O_TRUNC | O_CREAT, 0664);
    printf("fd_read = %d\n", fd_read);
    printf("fd_write = %d\n", fd_write);
    printf("error = %d\n", errno);
    while ((ret = read(fd_read, buf, sizeof(buf))) != 0)
    {
        write(fd_write, buf, ret);
    }
    close(fd_read);
    close(fd_write);
    printf("close file with fd = %d\n", fd_read);
    printf("close file with fd = %d\n", fd_write);
    return 0;
}
