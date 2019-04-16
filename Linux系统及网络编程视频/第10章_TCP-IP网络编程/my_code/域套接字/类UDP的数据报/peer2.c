#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <sys/un.h>

#define SOCK_FILE "./sock_peer2"

#define print_error(str) \
do{\
    fprintf(stderr, "File %s, Line %d, Function %s error\n",__FILE__, __LINE__, __func__);\
    perror(str);\
    exit(-1);\
}while(0);

int skfd = -1; // 两个UDP进程进行通信的fd
struct sockaddr_un peer_addr = {0};  // 存放UDP对端的信息比如协议和套接字文件地址

/* tcp通信时发送的数据(send函数使用)，这里以一个学生信息为例，用于第3、4步 */
typedef struct tcpdata{
    unsigned int stu_num; // 学号,无符号整型
    char stu_name[30]; // 学生姓名
}student;


/* 线程处理函数，用于从读取客户端发送过来的消息,用于第6步 */
void *pth_func(void *path_arg)
{
    int ret = -1;
    student stu_data = {0};
    unsigned int peer_addr_size = 0;

    while(1){
        bzero(&stu_data, sizeof(stu_data)); // 清空结构体中的数据
        peer_addr_size = sizeof(peer_addr); // 设置信息题大小
        ret = recvfrom(skfd, (void*)&stu_data, sizeof(stu_data), 0, (struct sockaddr *)&peer_addr, &peer_addr_size); 
        if(ret == -1) print_error("recvfrom fail");
        printf("student number = %d\n", ntohl(stu_data.stu_num)); // 打印学号，记得把数据从网络端序转为主机断端序
        printf("student name = %s\n", stu_data.stu_name); // 1个字符存储的无需进行端序转换
    } 
}

/* 信号处理函数，用于接收外部信号停止服务器线程 */
void signal_func(int signo)
{
    if(signo == SIGINT){
        remove(SOCK_FILE);
        exit(0); // 退出服务器进程
    }
}

int main(int argc, char const *argv[])
{
    
    if(argc != 2){
        printf("you must offer ip and port of peer!\n");
        exit(-1);
    }
    int ret = 0;

    /* 第5步：注册信号处理函数，用于关闭socket和退出线程 */
    signal(SIGINT, signal_func);

    /* 第1步：创建使用TCP协议通信的套接字文件，客户端的套接字直接用于和服务器端通信*/
    skfd = socket(AF_UNIX, SOCK_DGRAM, 0); // 一定注意第二个参数和TCP通信的不同
    if(skfd == -1) print_error("socket fail");
    
    /* 第2步：bind绑定固定的ip和端口 */
    struct sockaddr_un self_addr; 
    self_addr.sun_family = AF_UNIX; // 使用是IPV4 TCP/IP协议族的ip地址(32位)
    strcpy(self_addr.sun_path, SOCK_FILE);
    ret = bind(skfd, (struct sockaddr *)&self_addr, sizeof(self_addr)); // 绑定信息，记住第二个参数需要进行强制转换
    if(ret == -1) print_error("bind fail");
    
    
    /* 第4步：注册线程函数，用于对端的消息 */
    pthread_t recv_thread_id; // 接收对端消息的线程id
    ret = pthread_create(&recv_thread_id, NULL, pth_func, NULL); // 注册消息接收线程
    if(ret != 0) print_error("pthread_create fail");

    /* 第3步：调用调用sendto给指定同伴发送数据 */
    student stu_data = {0};
    unsigned int tmp_num; // 定义临时变量用于字节序转换
    while(1){
        // 设置对端UDP套接字的信息
        peer_addr.sun_family = AF_UNIX; // 使用是IPV4 TCP/IP协议族的ip地址(32位)
        strcpy(peer_addr.sun_path, argv[1]); // 命令行传参得到对方UDP套接字文件路径
        bzero(&stu_data, sizeof(stu_data)); // 清空结构体中的数据
        // 获取学生学号,但是需要从主机端序转换为网络端序
        printf("Please input student number:\n"); 
        scanf("%d", &tmp_num);
        stu_data.stu_num = htonl(tmp_num);
        // 获取学生姓名，不需要进行端序转换,因为字符数组以一个字节为单位进行存储
        printf("Please input student name:\n"); // 获取学生姓名
        scanf("%s", stu_data.stu_name);
        // 根据skfd向指定的UDP对端发送数据
        ret = sendto(skfd, (void *)&stu_data, sizeof(stu_data), 0, (struct sockaddr *)&peer_addr, sizeof(peer_addr));
        if(ret == -1) print_error("sendto fail");
    }

    return 0;
}
