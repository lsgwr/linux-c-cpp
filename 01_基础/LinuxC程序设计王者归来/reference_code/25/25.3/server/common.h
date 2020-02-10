#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include "iolib.h"		 /* 自制的I/O库函数 */

/* 全局宏定义区 */
#define MAX_LINE 1024	 /* 向客户端发送的应答信息的最大长度 */
#define PORT 8000		 /* 端口号 */
#define ADDR_LEN 17		 /* 十进制点分格式地址的长度，包括字符串结束符 */
#define NAME_LEN 256

/* 函数结构声明区 */
/* command.c 定义命令函数 */
extern int init(struct sockaddr_in *sin, int *lfd, int sock_opt);
										 /* 初始化服务器程序 */
extern int do_put(int cfd, char *file); /* 处理用户的get命令 */
extern int do_get(int cfd, char *file); /* 处理用户的put命令 */
extern int do_cd(int cfd, char *path);	 /* 处理!cd命令 */
extern int do_ls(int cfd, char  *path);	 /* 处理!ls命令 */
