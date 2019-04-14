#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define print_error(str) \
do{\
    fprintf(stderr, "File %s, Line %d, Function %s error\n",__FILE__, __LINE__, __func__);\
    perror(str);\
    exit(-1);\
}while(0);

int main(int argc, char const *argv[])
{
    int ret = -1;

    /* 第1步：创建使用TCP协议通信的套接字文件*/
    int skfd = -1;
    skfd = socket(AF_INET, SOCK_STREAM, 0);
    if(skfd == -1) print_error("socket fail");
    
    /* 第2步：调用bind绑定服务器的套接字、ip、端口 */
    struct sockaddr_in server_addr; 
    server_addr.sin_family = AF_INET; // 使用是IPV4 TCP/IP协议族的ip地址(32位)
    server_addr.sin_port = htons(5006); // 指定端口
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 服务器IP 
    ret = bind(skfd, (struct sockaddr *)&server_addr, sizeof(server_addr)); // 绑定信息，记住第二个参数需要进行强制转换
    if(ret == -1) print_error("bind fail");

    /* 第3步：调用listen 网络API，将套接字文件描述符，从主动变为被动文件描述符，用于被动监听客户的连接 */
    ret = listen(skfd, 3);
    if(ret == -1) print_error("listen fail");

    /* 第4步：调用accept 网络API，被动监听客户发起三次握手的连接请求，三次握手成功，即建立连接成功. 被动监听客户的连接也被称为监听客户上线的过程*/
    int cfd = -1; // 客户端用于和服务器端通信的fd
    struct sockaddr_in clnaddr = {}; // clnaddr : client address,用于存储客户端信息(ip和端口)的结构体
    unsigned int clnaddr_size = sizeof(clnaddr);
    cfd = accept(skfd, (struct sockaddr *)&clnaddr, &clnaddr_size); // 接收客户端相关的信息，成功返回客户端用于和服务器端通信的fd
    if(cfd == -1) print_error("accept fail");
    printf("cln_port= %d, cln_addr=%s\n", ntohs(clnaddr.sin_port), inet_ntoa(clnaddr.sin_addr)); // 打印客户端端口和IP，一定要先进行端序转换
    return 0;
}
