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
    int skfd = -1;
    /* 第1步：创建使用TCP协议通信的套接字文件*/
    skfd = socket(AF_INET, SOCK_STREAM, 0);
    if(skfd == -1) print_error("socket fail");
    
    struct sockaddr_in addr; // 必须引入arpa/inet.h
    addr.sin_family = AF_INET; //使用是IPV4 TCP/IP协议族的ip地址(32位)
    addr.sin_port   = htons(5006);//指定端口
    addr.sin_addr.s_addr = inet_addr("192.168.1.105");//指定ip地址
    ret = bind(skfd, (struct sockaddr*)&addr, sizeof(addr));
    return 0;
}
