// ioctl使用：获取terminal大小
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

int main(void){
    // 窗口大小的结构体
    struct winsize size;
    // isatty()判断是否是一个tty(终端)文件
    if(isatty(STDOUT_FILENO) == 0){
        // 是终端返回非零值，返回0表示不是终端文件
        exit(1);
    }
    // TIOCGWINSZ表示默认终端的大小，小于0表示返回错误
    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) < 0){
        perror("ioctl TIOCGWINSZ error");
        exit(1);
    }
    printf("%d rows, %d columns\n", size.ws_row, size.ws_col);
    return 0;
}
