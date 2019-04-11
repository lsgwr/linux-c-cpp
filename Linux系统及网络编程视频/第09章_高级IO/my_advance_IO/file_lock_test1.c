#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>

#define FCNTL_FILE "./file"

#define print_error(str) \
do{\
    fprintf(stderr, "File %s, Line %d, Function %s error\n",__FILE__, __LINE__, __func__);\
    perror(str);\
    exit(-1);\
}while(0);

int main(int argc, char const *argv[])
{
    int fd = 0;
    int ret = 0;

    fd = open(FCNTL_FILE, O_RDWR|O_CREAT|O_TRUNC, 0664);
    if(fd == -1) print_error("open fail");

    ret = fork();

    if(ret > 0){
        // 父进程 
        while(1){
            write(fd, "hello ", 6);
            write(fd, "world\n", 6);
        }
    }else if (ret == 0){
        // 子进程
        while(1){
            write(fd, "hello ", 6);
            write(fd, "world\n", 6);
        }
    }
    
    return 0;
}
