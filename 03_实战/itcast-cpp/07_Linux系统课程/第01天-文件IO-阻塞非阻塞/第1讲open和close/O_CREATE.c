#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    // int open(const char *pathname, int flags); // O_CREAT表示文件不存在时就创建,第三个参数表明新创建的文件权限
    int fd = open("./data.txt", O_RDONLY | O_CREAT, 0777);
    printf("fd  = %d\n", fd);
    // 在unistd.h中
    close(fd);
    printf("close file of fd = %d\n", fd);
    return 0;
}
