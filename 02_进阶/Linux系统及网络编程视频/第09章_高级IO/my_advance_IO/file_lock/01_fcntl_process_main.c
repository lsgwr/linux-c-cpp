#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>
#include "file_lock.h"

#define FCNTL_FILE "./file"
#define COUNT 10000

int main(int argc, char const *argv[])
{
    int fd = 0;
    int ret = 0;

    fd = open(FCNTL_FILE, O_RDWR|O_CREAT|O_TRUNC, 0664);
    if(fd == -1) print_error("open fail");

    ret = fork();

    if(ret > 0){
        // 父进程 
        int i = 0;
        for(i = 0; i < COUNT; i++){
            SET_WRFLCK_W(fd, SEEK_SET, 0, 0); // 加阻塞写锁
            write(fd, "hello ", 6);
            write(fd, "world\n", 6);
            UNLCK(fd, SEEK_SET, 0, 0); // 解锁，在哪加就在哪减
        }
    }else if (ret == 0){
        // 子进程
        int i = 0;
        for(i = 0; i < COUNT; i++){
            SET_WRFLCK_W(fd, SEEK_SET, 0, 0); // 加阻塞写锁
            write(fd, "hello ", 6);
            write(fd, "world\n", 6);
            UNLCK(fd, SEEK_SET, 0, 0); // 解锁，在哪加就在哪减
        }
    }
    
    return 0;
}
