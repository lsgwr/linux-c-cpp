#include "sem.h"

/**
 * 获取信号量需要的标识符
 * 
 * @param nsems 信号量的个数
 **/
int create_or_get_sem(int nsems)
{
    int semid = -1; // 信号量的id
    key_t key = -1; // 用于semget的第一个参数
    int fd = 0;     // 消息队列所需文件的文件描述符
    
    
    /* 1.保证消息队列需要的文件一定是存在的，不存在就创建 */
    fd = open(SEM_FILE, O_RDWR|O_CREAT, 0664); // 消息队列需要的文件
    if(fd == -1) print_error("open fail");
    
    /* 2.生成信号量需要的key */
    key = ftok(SEM_FILE, PROJ_ID);
    if(key == -1) print_error("ftok fail");
    
     /* 3.生成信号量的标识符 */
    semid = semget(key, nsems, 0664|IPC_CREAT);
    if(semid == -1) print_error("semget fail");
    
    return semid;
}
