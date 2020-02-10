#include "sem.h"
#define NSEMS 1 // 信号量个数，互斥只需要一个信号量

int semid = -1;

/**
 * 处理Ctrl+C信号，清理信号量和相关文件并退出进程
 **/ 
void signal_func(int signo)
{
    del_sem(semid, NSEMS);
    exit(-1);
}

int main(void)
{
    /* 0.打开或者创建信号量文件 */
    int fd = -1;
    fd = open("./file", O_RDWR|O_CREAT|O_TRUNC, 0664);
	if(fd == -1) print_error("open file fail");

    /* 1.创建信号量集合 */
    semid = create_or_get_sem(NSEMS); // 子进程会集成父进程数据
    
    /* 2.初始化信号量集合中的所有信号 */
    int i = 0;
    for(i = 0; i < NSEMS; i++){
        init_sem(semid, i, 1); // 实际互斥只需要一个信号量
    }
    
    /* 3.创建子进程 */    
    int ret = -1;
    ret = fork();
    
    /* 4.父子进程利用信号量集合实现互斥地向文件写入数据 */
    if(ret > 0){
        // 父进程
        signal(SIGINT, signal_func); // 注册信号处理函数
        while(1){
            write(fd, "hello ", 6);
            write(fd, "world\n", 6);
        }
    }else if(ret == 0){
        // 子进程
        while(1){
            write(fd, "hhhhh ", 6);
            write(fd, "wwwww\n", 6);
        }
    }
    return 0;    
}
