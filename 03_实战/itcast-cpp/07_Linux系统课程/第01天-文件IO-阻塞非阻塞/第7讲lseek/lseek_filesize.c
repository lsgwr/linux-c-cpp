// lseek计算文件大小
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
    fd = open("lseek.txt", O_RDWR|O_CREAT|O_TRUNC, 0644);
    if (fd < 0) {
        perror("open lseek.txt error");
        exit(1);
    }
    // 偏移99个字节(占位符是文件空洞)，加上下面write一个字符。，一共100个，write是为了清缓存
    int ret = lseek(fd, 99, SEEK_SET);
    if (ret == -1) {
        perror("lseek error");
        exit(1);
    }
    // 写一次把缓冲写出去
    write(fd, "a", 1);

    // 利用lseek返回值看文件的大小
    int filesize = lseek(fd, 0, SEEK_END);
    printf("size of file lseek.txt is %d\n", filesize);
    close(fd);
    return 0;
}
