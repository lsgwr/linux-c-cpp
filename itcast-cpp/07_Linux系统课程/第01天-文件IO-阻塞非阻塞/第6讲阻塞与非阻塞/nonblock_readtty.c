// 非阻塞读，无限等待
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define MSG_TRY "try again\n"

int main(int argc, char const *argv[])
{
    char buf[10];
    int fd, n;
    // 使用O_NONBLOCK标志设置非阻塞读终端
    fd = open("/dev/tty", O_RDONLY | O_NONBLOCK);
    if (fd < 0) {
        perror("open /dev/tty");
        exit(1);
    }
tryagain:
    // printf("fd = %d\n", fd);
    // 错误 errno=EAGAIN或者EWOULDBLOCK
    n = read(fd, buf, 10);
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
    close(fd);
    return 0;
}
