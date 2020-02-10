// 把后者的文件描述符覆盖前面的文件描述符
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int fd1 = open("opendir.c", O_RDONLY);
    if (fd1 == -1) {
        perror("open fd1 error");
        exit(1);
    }
    printf("...fd1 = %d\n", fd1);
    
    int fd2 = open("getcwd.c", O_RDONLY);
    if (fd2 == -1) {
        perror("open fd2 error");
        exit(1);
    }
    printf("...fd2 = %d\n", fd2);
    
    int newFd = dup2(fd1, fd2);
    if (newFd == -1) {
        perror("dup error");
        exit(1);
    }
    printf("...newFd = %d\n", newFd);
    return 0;
}
