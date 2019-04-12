#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <poll.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>

#define print_error(str) \
do{\
    fprintf(stderr, "File %s, Line %d, Function %s error\n",__FILE__, __LINE__, __func__);\
    perror(str);\
    exit(-1);\
}while(0);

int main(void)
{
    int fd = 0;
    int ret = 0;
    int mousefd = 0;
    char buf0[100] = {0};
	int buf1 = 0; // 鼠标值是int型
    struct pollfd fds[2]; // 读的fd集合
        
    // 打开键盘输入
    mousefd = open("/dev/tty", O_RDONLY);
    if(mousefd == -1) print_error("open mouse0 fail");
    
    fds[0].fd = 0;
    fds[0].events = POLLIN;
    
    fds[0].fd = mousefd;
    fds[0].events = POLLIN;
        
    while(1){

label:  ret = poll(fds, 2, 3000); // 设置fd范围、个数和超时时间
        if((ret == -1)&&(errno==EINTR)) { // 如果函数执行失败或者中途被其他信号唤醒就返回重新执行
            goto label;
        }else if(ret == -1){
            print_error("poll fail");
        }else if(ret > 0){
            // 返回了有消息的fd, 下面判断不同的消息源来进行不同处理
            if(fds[0].events == fds[0].revents){
                bzero(buf0, sizeof(buf0));
                ret = read(fds[0].fd, buf0, sizeof(buf0));
                if(ret > 0) printf("%s\n", buf0);
            }
            
             if(fds[1].events == fds[1].revents){
                bzero(&buf1, sizeof(buf1));
                ret = read(fds[1].fd, &buf1, sizeof(buf1));
                if(ret > 0) printf("%d\n", buf1);
            }
        }
        
    }
    return 0;
}
