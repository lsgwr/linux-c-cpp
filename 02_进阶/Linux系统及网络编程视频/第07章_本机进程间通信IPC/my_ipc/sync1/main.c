#include "sem.h"
#define NSEMS 3 // 信号量个数，同步需要多个信号量

int semid = -1;

/**
 * 处理Ctrl+C信号，清理信号量和相关文件并退出进程
 **/ 
void signal_func(int signo)
{
    del_sem(semid);
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
        if(i == 0){
            init_sem(semid, i, 1); // 编号为0的信号量(父进程),表示不阻塞
        }else{
            init_sem(semid, i, 0); // 其他两个子进程先阻塞着,设置为0
        }
    }
    
    /* 3.创建子进程 */    
    int ret = -1;
    ret = fork();
    
    int semnum_arr[1] = {0}; // 这个例子同时也只允许一个信号量工作，所以数组大小只需要为1
    
    /* 4.父子进程利用信号量集合实现互斥地向文件写入数据 */
    if(ret > 0){
        ret = fork(); // 父进程再fork一个进程
        if(ret > 0){
            // 父进程
            
            while(1){
                semnum_arr[0] = 0; // 设置要操作的信号量的编号
                p_sem(semid, semnum_arr, 1); // p操作
                printf("000000\n");
                sleep(1);
                semnum_arr[0] = 1; // 设置要操作的信号量的编号
                v_sem(semid, semnum_arr, 1); // v操作
            }
        }else if(ret == 0){
            // 子进程2
            while(1){
                semnum_arr[0] = 2; // 设置要操作的信号量的编号
                p_sem(semid, semnum_arr, 1); // p操作
                printf("222222\n");
                sleep(1);
                semnum_arr[0] = 0; // 设置要操作的信号量的编号
                v_sem(semid, semnum_arr, 1); // p操作
            }
        }
    }else if(ret == 0){
        // 子进程1
        signal(SIGINT, signal_func); // 注册信号处理函数，在父进程中处理就好了
        while(1){
            semnum_arr[0] = 1; // 设置要操作的信号量的编号
            p_sem(semid, semnum_arr, 1); // p操作
            printf("111111\n");
            sleep(1);
            semnum_arr[0] = 2; // 设置要操作的信号量的编号
            v_sem(semid, semnum_arr, 1); // v操作
        }
    }
    return 0;    
}
