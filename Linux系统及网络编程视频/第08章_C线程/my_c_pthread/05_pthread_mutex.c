#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SUB_THREAD_NUM 2 // 次线程(主线程以外的线程)的个数
#define PTHREAD_FILE "./pthread_file" // 线程操作的文件

#define print_error_thread(str, errno) \
do{\
    fprintf(stderr, "File %s, Line %d, Function %s error\n",__FILE__, __LINE__, __func__);\
    printf("%s:%s", str, strerror(errno));\
    exit(-1);\
}while(0);

#define print_error(str) \
do{\
    fprintf(stderr, "File %s, Line %d, Function %s error\n",__FILE__, __LINE__, __func__);\
    perror(str);\
    exit(-1);\
}while(0);


typedef struct pthread_arg{
    pthread_t tid;
    int no; // 次线程编号
    int fd; // 打开文件的文件描述符
}pth_arg;

/* 全局变量 */
pth_arg pth_arg_arr[SUB_THREAD_NUM]; // 声明结构体数组,存放线程信息
int exit_flag = 0; // 主线程退出标志
pthread_mutex_t mutex; // 线程互锁

void process_exit_deal(void)
{
    printf("process exit~\n");
}


/**
 * 线程退出处理函数(atexit是进程退出处理函数)
 * */
void pthread_exit_deal(void *arg)
{
    pth_arg* pth_arg_obj = (pth_arg*)arg; // 入参从void*强制转换为pth_arg类型，void*方便传入各种数据类型
    printf("pthread exit, No = %d, Id = %ld\n", pth_arg_obj->no, pth_arg_obj->tid);
}

/* 返回值和形参类型必须都是void*方便自己定义数据类型 */
void *pth_func(void *arg)
{
    printf("tid = %ld\n", pthread_self()); // 获取进程tid
    pth_arg* pth_arg_obj = (pth_arg*)arg; // 入参从void*强制转换为pth_arg类型，void*方便传入各种数据类型
    printf("pthread No = %d, Id = %ld\n", pth_arg_obj->no, pth_arg_obj->tid);
    
    // pthread_detach(pthread_self()); // 线程把自己分离出去,注意不能和pthread_join一起用
    
    pthread_cleanup_push(pthread_exit_deal, arg); // 线程退出处理函数
    
    int fd = pth_arg_obj->fd;
    while(1){
        pthread_mutex_lock(&mutex);
        write(fd, "hello ", 6);
        write(fd, "world\n", 6);
        pthread_mutex_unlock(&mutex);
    }
    
    pthread_cleanup_pop(!0); // 这个pop必须写上好和上面的push配对，否则会报奇怪的错
    
    return NULL;
    // pthread_exit(NULL); // 退出线程，和return NULL等效
}

void signal_func(int signo)
{
    if(SIGALRM == signo){
        int i = 0;
        for(i = 0; i < SUB_THREAD_NUM; i++){
            pthread_cancel(pth_arg_arr[i].tid); // 取消所有子线程
        }
    }
    // exit(-1); // 这里不能直接exit，因为会退出整个进程,pthread_join不会执行到
    exit_flag = 1; // 表示次线程都退出了，父线程也可以退出了，在main里的while(1)里break
}



int main()
{
    int i = 0;
    int ret = 0;
    int fd = 0;
    
    // 注册进程退出处理函数，exit正常终止进程,atexit是c标准库函数
    atexit(process_exit_deal);
    
    // 初始化线程互斥锁
    ret = pthread_mutex_init(&mutex, NULL);
    if(ret != 0) print_error("pthread_mutex_init fail");

    fd = open(PTHREAD_FILE, O_RDWR|O_CREAT|O_TRUNC, 0664);
    if(fd == -1) print_error("open fail");
    
    // 循环创建多个次线程
    for(i = 0; i < SUB_THREAD_NUM; i++){
        pth_arg_arr[i].fd = fd; // 赋值文件描述符
        pth_arg_arr[i].no = i; // 给线程进行编号
        // 同一个函数可以被多次注册; 第四个参数表示传入对应的结构体对象
        ret = pthread_create(&pth_arg_arr[i].tid, NULL, pth_func, (void *)&pth_arg_arr[i]); 
        // pthread_create函数不会设置errno，知会返回错误号， 所以不能直接用perror，只能自己用strerror翻译错误号
        if(ret != 0) print_error_thread("pthread_create fail", ret);
    }
    /* 定时1s，时间到后在信号处理函数中调用pthread_cancel函数取消线程 */
    signal(SIGALRM, signal_func);
    alarm(1);
    
    void *retval = NULL; // 用于存储pthread_join函数返回值
    for(i = 0; i < SUB_THREAD_NUM; i++){
        pthread_join(pth_arg_arr[i].tid, &retval);
        printf("return val = %ld\n", (long)retval);
    }
    
    // 主线程也输出内容
    while(1){ // 主线程不能先死，要不子线程也得死; 子线程死，父线程还能接着存活
        pthread_mutex_lock(&mutex);
        write(fd, "hello ", 6);
        write(fd, "world ", 6);
        write(fd, "main\n", 5);
        pthread_mutex_unlock(&mutex);
        if(exit_flag){
            break; // 次线程都退出了子线程再退出
        }
    }
    
    return 0;
}

/**输出如下

tid = 140324015236864
pthread No = 1, Id = 140324015236864
tid = 140324023629568
pthread No = 0, Id = 140324023629568
pthread exit, No = 1, Id = 140324015236864
pthread exit, No = 0, Id = 140324023629568
return val = -1
return val = -1
process exit~
**/
