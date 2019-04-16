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

#define SERVER_PORT 5001 // 服务器进行对外的端口
#define SERVER_IP "127.0.0.1" // 服务器所在机器的IP

#define print_error(str) \
do{\
    fprintf(stderr, "File %s, Line %d, Function %s error\n",__FILE__, __LINE__, __func__);\
    perror(str);\
    exit(-1);\
}while(0);

#define print_error_thread(str, errno) \
do{\
    fprintf(stderr, "File %s, Line %d, Function %s error\n",__FILE__, __LINE__, __func__);\
    printf("%s:%s", str, strerror(errno));\
    exit(-1);\
}while(0);

/* tcp通信时发送的数据(send函数使用)，这里以一个学生信息为例，用于第5步 */
typedef struct tcpdata{
    unsigned int stu_num; // 学号,无符号整型
    char stu_name[30]; // 学生姓名
}student;

/* 线程处理函数，用于从读取客户端发送过来的消息,用于第6步 */
void *pth_func(void *pth_arg)
{
    int ret = 0;
    
    long cfd = (long)pth_arg; // 存放客户端的通信fd
    
    student stu_data = {0};
    char msg[] = "msg from server: recv ok!\n";
    while(1){
        bzero(&stu_data, sizeof(stu_data)); // 清空结构体中的数据
        ret = recv(cfd, (void *)&stu_data, sizeof(stu_data), 0); 
        if(ret == -1) print_error("recv fail");
        // 打印客户端传过来的数据并给客户端回复个消息
        printf("student number = %d\n", ntohl(stu_data.stu_num)); // 打印学号，记得把数据从网络端序转为主机断端序
        printf("student name = %s\n", stu_data.stu_name); // 1个字符存储的无需进行端序转换
        // 给客户端回个消息
        ret = send(cfd, msg, sizeof(msg), 0);
        if(ret == -1) print_error("send fail");
    } 
}

/* 信号处理函数，用于接收外部信号停止服务器线程 */
void signal_func(int signo)
{
    if(signo == SIGINT){
        exit(0); // 退出服务器进程
    }
}

int main(int argc, char const *argv[])
{
    int ret = -1;

    /* 第7步：注册信号处理函数，用于关闭socket和退出线程 */
    signal(SIGINT, signal_func);

    /* 第1步：创建使用TCP协议通信的套接字文件*/
    int skfd = -1;
    skfd = socket(AF_INET, SOCK_STREAM, 0);
    if(skfd == -1) print_error("socket fail");
    
    /* 第2步：调用bind绑定服务器的套接字、ip、端口 */
    struct sockaddr_in server_addr; 
    server_addr.sin_family = AF_INET; // 使用是IPV4 TCP/IP协议族的ip地址(32位)
    server_addr.sin_port = htons(SERVER_PORT); // 指定端口
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP); // 服务器IP 
    ret = bind(skfd, (struct sockaddr *)&server_addr, sizeof(server_addr)); // 绑定信息，记住第二个参数需要进行强制转换
    if(ret == -1) print_error("bind fail");

    /* 第3步：调用listen 网络API，将套接字文件描述符，从主动变为被动文件描述符，用于被动监听客户的连接 */
    ret = listen(skfd, 3);
    if(ret == -1) print_error("listen fail");

    long cfd; // 存储服务器端和制定客户端通信的fd，一个客户端就需要服务器端分配一个cfd
    pthread_t recv_thread_id; // 接收客户端消息的线程id

    while(1){
        // 第4步：监听客户端连接
        cfd = accept(skfd, NULL, NULL);
        if(cfd == -1) print_error("accept fail");
        
        // 第5步：注册消息接收线程,把专用的fd传给线程，方便服务器给指定线程回消息
        ret = pthread_create(&recv_thread_id, NULL, pth_func, (void *)cfd); 
        if(ret == -1) print_error_thread("pthread_create fail", ret); // 注意函数返回值用来设置perror
        // 因为一个服务器端对应多个客户端了，所以这里不能从服务器main函数直接向客户端发消息了，只能在线程里发
    }

    return 0;
}
