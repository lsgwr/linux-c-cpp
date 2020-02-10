// 改变文件属性的fcntl,见《Linux系统编程手册》P76
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSG_TRY "try again\n"

int main(int argc, char const *argv[])
{
    char buf[10];
    int flags, n;
    
    // 1.获取文件的文件标志
    flags = fcntl(STDIN_FILENO, F_GETFL);
    if (flags == -1) {
        perror("fcntl error");
        exit(1);
    }
    // 2.修改读写标志
    flags |= O_NONBLOCK;
    // 3.更新读写标志
    int ret = fcntl(STDIN_FILENO, F_SETFL, flags);
    if (ret == -1) {
        perror("fcntl error");
        exit(1);
    }
    tryagain:
    // printf("fd = %d\n", fd);
    // 错误 errno=EAGAIN或者EWOULDBLOCK
    n = read(STDIN_FILENO, buf, 10);
    if (n < 0) {
        // 由于open时指定了O_NONBLOCK标志，read读设备，没有数据到达返回1，同时将errno设置为EAGAIN或EWOULDBLOCK
        if (errno != EAGAIN) {
            perror("read /dev/tty");
            exit(1);
        }
        sleep(1);
        write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TRY));
        goto tryagain;
    }
    write(STDOUT_FILENO, buf, n);
    return 0;
}
