#include "sem.h"
#define NSEMS 1 // 信号量个数，互斥只需要一个信号量

int main(void)
{
    /* 打开文件 */
    int fd = -1;
    fd = open("./file", O_RDWR|O_CREAT|O_TRUNC, 0664);
	if(fd == -1) print_error("open file fail");

    /* 创建子进程 */    
    int ret = -1;
    ret = fork();
    
    /* 父子进程互斥地向文件写入数据 */
    if(ret > 0){
        // 父进程
        create_or_get_sem(NSEMS);
        // while(1){
            write(fd, "hello ", 6);
            write(fd, "world\n", 6);
        // }
    }else if(ret == 0){
        // 子进程
        create_or_get_sem(NSEMS);
        // while(1){
            write(fd, "hhhhh ", 6);
            write(fd, "wwwww\n", 6);
        // }
    }
    return 0;    
}
