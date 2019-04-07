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
 * 
 * @param semid 信号量集合标识符id
 * @param nsems 信号量集合中的信号量个数
 **/ 
void del_sem(int semid, int nsems)
{
    int i = 0;
    int ret = -1;
    ret = semctl(semid, 0, IPC_RMID);
	if(ret == -1) print_error("semctl del sem fail");
    remove(SEM_FILE); // 删除信号量文件
}

/**
 * 信号量的P操作(P掉，减1)
 * 
 * @param semid 信号量集合标识符id
 * @param semnum_arr[] 信号量编号组成的数组
 * @param nsops 信号量编号数组的元素个数,用于给结构体数组ops[n]赋值
 **/ 
void p_sem(int semid, int semnum_arr[], int nsops)
{
    int ret = -1;
    struct sembuf sops[nsops];
    int i = 0;
    for(i = 0; i< nsops; i++){
        sops[i].sem_num = semnum_arr[i];
        sops[i].sem_op = -1; // p掉，减1
        sops[i].sem_flg = SEM_UNDO; // 防止死锁
    }
    ret = semop(semid, sops, nsops);
    if(ret == -1) print_error("semop p fail");
}

/**
 * 信号量的V操作(V先降后升，否极泰来，加1)
 * 
 * @param semid 信号量集合标识符id
 * @param semnum_arr[] 信号量编号组成的数组
 * @param nsops 信号量编号数组的元素个数,用于给结构体数组ops[n]赋值
 **/ 
void v_sem(int semid, int semnum_arr[], int nsops)
{
    int ret = -1;
    struct sembuf sops[nsops];
    int i = 0;
    for(i = 0; i< nsops; i++){
        sops[i].sem_num = semnum_arr[i];
        sops[i].sem_op = 1; // V先降后升，否极泰来，加1
        sops[i].sem_flg = SEM_UNDO; // 防止死锁
    }
    ret = semop(semid, sops, nsops);
    if(ret == -1) print_error("semop v fail");
}
