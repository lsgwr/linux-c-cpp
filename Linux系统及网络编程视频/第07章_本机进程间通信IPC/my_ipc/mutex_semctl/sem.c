#include "sem.h"

/**
 * 获取信号量集合需要的标识符id
 * 
 * @param nsems 信号量集合中的信号量个数
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

/**
 * 初始化信号量编号
 * 
 * @param semid 信号量集合标识符id
 * @param semnum 信号量在信号量集合中的编号
 * @param val 用于设置信号量编号的值
 **/ 
void init_sem(int semid, int semnum, int val)
{
    union semun sem_un;
    sem_un.val = val;  //现在整个联合体sem_un的值就是val
    int ret = semctl(semid, semnum, SETVAL, sem_un);
    if(ret == -1) print_error("semctl init fail");
}

/**
 * 删除信号量集合
 * @param semid 信号量集合标识符id
 * @param nsems 信号量集合中的信号量个数
 **/ 
void del_sem(int semid, int nsems)
{
    int i = 0;
    int ret = -1;
    for(i = 0; i < nsems; i++){
        ret = semctl(semid, i, IPC_RMID); // 删除信号量集合中的第i个信号量
        if(ret == -1) print_error("semctl del fail");
    }
    remove(SEM_FILE); // 删除信号量文件
}
