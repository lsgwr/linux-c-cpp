#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

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
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    return 0;
}
