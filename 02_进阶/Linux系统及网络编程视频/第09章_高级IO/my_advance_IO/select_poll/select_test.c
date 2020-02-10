#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
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
    int ret = 0;
    int mousefd = 0;
    char buf1[100] = {0};
	int buf2 = 0; // 鼠标值是int型
    fd_set readfds; // 读的fd集合
    struct timeval timeover; // 超时设置
    
    // 打开键盘输入
    mousefd = open("/dev/tty", O_RDONLY);
    if(mousefd == -1) print_error("open mouse0 fail");
    
    while(1){

        FD_ZERO(&readfds); // 将整个集合全部清空
        FD_SET(0, &readfds); // 将值为0的文件描述符放到集合set中
        FD_SET(mousefd, &readfds); // 将值为mousefd的文件描述符放到集合set中
        
        /* 设置超时时间 */
	    timeover.tv_sec = 3;	
	    timeover.tv_usec = 0;

label:  ret = select(mousefd + 1, &readfds, NULL, NULL, &timeover); // 设置fd范围
        if((ret == -1)&&(errno==EINTR)) { // 如果函数执行失败或者中途被其他信号唤醒就返回重新执行
            goto label;
        }else if(ret == -1){
            print_error("select fail");
        }else if(ret > 0){
            
            // 返回了有消息的fd, 下面判断不同的消息源来进行不同处理
            if(FD_ISSET(0, &readfds)){
                bzero(buf1, sizeof(buf1));
				ret = read(0, buf1, sizeof(buf1)); // 标准读入	
				if(ret > 0) printf("%s\n", buf1);
			}
			
			if(FD_ISSET(mousefd, &readfds))
			{
				bzero(&buf2, sizeof(buf2));
				ret = read(mousefd, &buf2, sizeof(buf2));	// 鼠标读入
				if(ret > 0) printf("%d\n", buf2);
			}
        }
        
    }
    return 0;
}
