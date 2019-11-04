#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    int fd, n;
    char msg[] = "it's a test for lseek!";
    char ch;
    fd = open("lseek.txt", O_RDWR|O_CREAT, 0644);
    if (fd < 0) {
        perror("open lseek.txt error");
        exit(1);
    }
    // 使用fd对打开的文件进行写操作，文件读写位置位于文件结尾处，不会读到任何内容
    write(fd, msg, strlen(msg));
    lseek(fd, 0, SEEK_SET); // 修改文件读写指针位置，位于文件开头，注释该行会怎么样？
    while((n = read(fd, &ch, 1))){
        if (n < 0) {
            perror("read error");
            exit(1);
        }
        // 文件按字节读出，写出到屏幕上
        write(STDOUT_FILENO, &ch, n);
    }
    close(fd);
    return 0;
}
